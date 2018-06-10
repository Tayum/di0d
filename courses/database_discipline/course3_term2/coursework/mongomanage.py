from pymongo import MongoClient
from wa_api import WA_API

# Collection Names
AC = "archers"
CC = "competitions"
QC = "qualifications"
QAC = "qualifications_arrows"


class MongoManage:
    def __init__(self, host='localhost', port=27017, rs=None):
        if rs:
            self.client = MongoClient(host=host, port=port, replicaset=rs, readPreference='primaryPreferred')
        else:
            self.client = MongoClient(host=host, port=port)
        self.db = None

    def set_database(self, db_name='wa'):
        self.db = self.client[db_name]

    def insert(self, collection, obj):
        """
        Insert for the collections with no dependencies with other collections
        OR where dependencies has already been resolved
        """
        try:
            result = self.db[collection].insert_one(obj)
            return result.inserted_id
        except:
            print("{0} collection: failed to insert object: {1}".format(collection, obj))
            return -1

    def insert_qualification(self, qualification):
        competition_id = self.db[CC].find_one({'wa_id': qualification['competition_id']})['_id']
        qualification['competition_id'] = competition_id

        wa_archer_ids = [aid for aid in qualification['archer_ids']]
        archer_ids = []
        for wa_ai in wa_archer_ids:
            try:
                aid = self.db[AC].find_one({'wa_id': wa_ai})['_id']
            except TypeError:
                # if no such archer is found in MongoDB, find him via API and add him
                print("Archer with {0} World Archer ID was not found in the DB, inserting it...")
                wa = WA_API()
                archer = wa.db__get_single_archer(wa_ai)
                aid = self.insert(AC, archer)
                print("...inserting of archer is done, _id: {0}".format(aid))
            archer_ids.append(aid)
        qualification['archer_ids'] = archer_ids

        try:
            result = self.db[QC].insert_one(qualification)
            return result.inserted_id
        except:
            print("Qualifications collection: failed to insert qualification: {0}".format(qualification))
            return -1

    def get_qualifications(self, individual_team=None):
        """
        :param individual_team:
            1 - return only individual qualification results
            2 - return only team qualification results
            (others) - return both
        """
        if individual_team == 1:
            qualifications = self.db[QC].find({"is_team": 0})
        elif individual_team == 2:
            qualifications = self.db[QC].find({"is_team": 1})
        else:
            qualifications = self.db[QC].find()

        # populate the Competitions and Archers Collections
        qualifications = list(qualifications)
        for i in range(0, len(qualifications)):
            qualifications[i]['competition_id'] = self.db[CC].find_one({
                "_id": qualifications[i]['competition_id']
            })['wa_id']

            qualifications[i]['archer_ids'] = [self.db[AC].find_one({
                "_id": aid
            })['wa_id'] for aid in qualifications[i]['archer_ids']]

        return qualifications

    def get_arrows_within_competition(self, competition_wa_id):
        competition_id = self.db[CC].find_one({"wa_id": competition_wa_id})['_id']

        qualifications = self.db[QC].find({"competition_id": competition_id, "is_team": 0})
        qualification_ids = [q['_id'] for q in qualifications]

        qualification_arrows = self.db[QAC].find({"qualification_id": {"$in": qualification_ids}})
        qualification_arrows = [qa['arrows'] for qa in qualification_arrows]

        arrows = []
        for arrows_list in qualification_arrows:
            arrows.extend(arrows_list)
        return arrows

    def get_competitions(self):
        competitions = self.db[CC].find()
        return list(competitions)

    def get_individual_qualification_scores_within_competition(self, competition_wa_id):
        competition_id = self.db[CC].find_one({"wa_id": competition_wa_id})['_id']
        qualifications = self.db[QC].find({"competition_id": competition_id, "is_team": 0})
        return list(qualifications)

    def get_maximum_individual_qualification_score(self):
        male = self.db[QC].find({'is_team': 0, 'category': 'RM'}).sort([('score', -1)]).limit(1)[0]
        female = self.db[QC].find({'is_team': 0, 'category': 'RW'}).sort([('score', -1)]).limit(1)[0]

        # populate the Competitions And Archers Collections
        male['competition_id'] = self.db[CC].find_one({'_id': male['competition_id']})
        female['competition_id'] = self.db[CC].find_one({'_id': female['competition_id']})
        male['archer_ids'] = self.db[AC].find_one({'_id': male['archer_ids'][0]})
        female['archer_ids'] = self.db[AC].find_one({'_id': female['archer_ids'][0]})
        return {
            "male": male,
            "female": female,
        }

    def get_archer_results(self, archer_wa_id):
        archer = self.db[AC].find_one({"wa_id": archer_wa_id})
        qualifications = self.db[QC].find({"archer_ids": archer['_id']})
        qualifications = list(qualifications)

        # populate the Competitions Collection
        for i in range(0, len(qualifications)):
            qualifications[i]['competition_id'] = self.db[CC].find_one({'_id': qualifications[i]['competition_id']})
        return {
            "archer": archer,
            "qualifications": qualifications,
        }

    def get_country_results(self, NOC):
        qualifications = self.db[QC].aggregate([
            {
                "$unwind": "$archer_ids",
            },
            {
                "$lookup":
                {
                    "from": AC,
                    "localField": "archer_ids",
                    "foreignField": "_id",
                    "as": "archers",
                },
            },
            {
                "$match": {"{0}.NOC".format(AC): NOC},
            },
        ])

        # The Mongo Request above does return a little broken results
        # So that's why we have to adjust and combine them a bit
        qualifications = list(qualifications)
        unique_qualifications = list({q['_id']: q for q in qualifications}.values())
        for q in qualifications:
            for i in range(0, len(unique_qualifications)):
                if q['_id'] == unique_qualifications[i]['_id']:
                    for archer in unique_qualifications[i]['archers']:
                        if archer['wa_id'] == q['archers'][0]['wa_id']:
                            break
                    else:
                        unique_qualifications[i]['archers'].append(q['archers'][0])

        # For each of unique qualifications,
        # populate the Competitions Collection
        # and delete the unnecessary "archer_ids" field
        for i in range(0, len(unique_qualifications)):
            unique_qualifications[i]['competition_id'] = self.db[CC].find_one({"_id": unique_qualifications[i]['competition_id']})
            try:
                del unique_qualifications[i]['archer_ids']
            except KeyError:
                pass

        return unique_qualifications
