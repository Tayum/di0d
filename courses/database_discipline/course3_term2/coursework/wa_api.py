import requests
import json

import urllib3
urllib3.disable_warnings()


def _unpack_list_of_lists(list_of_lists):
    return [el for single_list in list_of_lists for el in single_list]


# World Archery API
class WA_API:
    """
    CLASS FOR WORKING WITH WORLD ARCHERY API TO GET THE DESIRED RESULTS

    WAS USED BEFORE THE DATABASE WAS CREATED

    FUNCTIONS THAT START WITH db_ SHOULD ONLY BE USED WHEN FILLING DB WITH RESULTS
    """
    def __init__(self):
        self.base_url = "https://secret.net"  # Provided by World Archery link


    def __get(self, querystring, as_json=True, info="items"):
        """
        :param querystring:
            querystring is a dictionary with URL parameters
        :param as_json:
            True - Use json.loads() to create a dictionary from the response from API
            False - return response and plain HTML
        :param info:
            "items" - will return only items from response
            "pageInfo" - will return only pageInfo from response
            (others) - return both
        """
        # add the default parameter to query
        querystring['v'] = "3"
        response = requests.request("GET", self.base_url, params=querystring, verify=False)

        if not as_json:
            return response.text

        js = response.text
        js = json.loads(js)
        if info == "items":
            return js['items']
        elif info == "pageInfo":
            return js['pageInfo']
        else:
            return js

    def get_athlete_biography(self, athlete_id):
        """
        For a single athlete by athlete_id, returns athlete bio
        """
        querystring = {"content": "ATHLETEBIOGRAPHY", "Id": athlete_id}
        bio = self.__get(querystring)[0]
        bio = dict({
            "athlete_id": bio["Id"],
            "name": bio["FName"] + " " + bio["GName"],
            "gender": bio["Gender"],
            "country": bio["CountryShort"],
            "NOC": bio["NOC"],
            "age": bio["Age"],
            # RW or RM
            "category_code": "R" + bio["Gender"],
            # if there is current rank, assign it. If not, assign None
            "world_rank": bio["WorldRankings"]["Current"][0]["Rnk"] if bio["WorldRankings"]["Current"] else None
        })
        return bio

    def get_olympic_ids(self):
        """
        Gets all the competition_id's of the Olympic Games (starting from 2000 and to 2016, those with results)

        RETURNS:
            list() of competition_id's
        """
        querystring = {"content": "COMPETITIONS", "LevelId": "1", "WithResults": "1", "StartDate": "2000-01-01", "RBP": "All"}
        # select only those Olympic Games with "ComSubLevel": 1 (exclude "ComSubLevel": 2 - Para and "ComSubLevel": 3 - Youth)
        # and those with Date >= 2000-01-01 (the newest ones)
        return [competition['ID'] for competition in self.__get(querystring) if competition['ComSubLevel'] == 1]

    def get_athletes_by_competition(self, competition_id):
        """
        Gets all the athletes that were performing in the competition with competition_id

        RETURNS:
            list() of dict({"athlete_id": int, "athlete_category": str})
                with athlete_id's and category, that athlete were performing in
                "athlete_category" possible values: "RM" [Recurve Men] OR "RW" [Recurve Women]
        """
        querystring = {"content": "ENTRIES", "CompId": competition_id, "RBP": "All"}
        items = self.__get(querystring)
        athletes = [{'athlete_id': item['Athlete']['Id'], 'athlete_category': item['CatInd'][0]['Code']} for item in items]
        return athletes

    def get_scores_by_competition(self, competition_id, sex=None):
        """
        :param sex:
            1 - return only male scores
            2 - return only female scores
            (others) - return both

        Gets individual qualifications results for each athlete that was performing in these competition

        RETURNS:
            dict({"male": list(), "female": list()})
                of male and female results respectively
        """
        querystring = {"content": "INDIVIDUALQUALIFICATIONS", "CompId": competition_id, "RBP": "All"}
        items = self.__get(querystring)
        if sex == 'M':
            male_scores = [item['Results'] for item in items if item['Code'] == "RM"][0]
            female_scores = None
        elif sex == 'F':
            male_scores = None
            female_scores = [item['Results'] for item in items if item['Code'] == "RW"][0]
        else:
            male_scores = [item['Results'] for item in items if item['Code'] == "RM"][0]
            female_scores = [item['Results'] for item in items if item['Code'] == "RW"][0]

        scores = dict()
        scores['male'] = [score['Score'] for score in male_scores] if male_scores else []
        scores['female'] = [score['Score'] for score in female_scores] if female_scores else []
        return scores

    def get_athlete_arrows_in_competition(self, competition_id, athlete_id, category_code):
        """
        Gets the individual qualification results by arrows (i.e. 72 arrows)
        (for one athlete with athlete_id within a competition_id competition)

        RETURNS:
            list() of str's with len() == 72, each str represents one arrow
            possible values for each arrow: "1" to "10", "X", "M" (X should be interpreted as "10", M - as "0")
        """
        querystring = {"content": "INDIVIDUALQUALIFICATIONARROWS", "CompId": competition_id, "Id": athlete_id, "CatCode": category_code}
        distances = self.__get(querystring)
        end_lists = [distance['Ends'] for distance in distances]
        ends = _unpack_list_of_lists(end_lists)
        arrow_lists = [end['Arrows'] for end in ends]
        arrows = _unpack_list_of_lists(arrow_lists)
        return arrows

    def get_arrows_in_competition(self, competition_id):
        """
        Gets the list of individual qualification results by arrows (i.e. 72 arrows each) for the competition_id
        (for each of the athletes that performed in the competition)

        RETURNS:
            list() of list()'s (each with len() == 72).
            Each list() that is inside represents 72 arrows (i.e. one qualification)
            Each str inside these lists represents one arrow
            possible values for each arrow: "0" to "10" and "X" (X should be interpreted as "10")
        """
        athletes = self.get_athletes_by_competition(competition_id)
        arrows_results = [
            self.get_athlete_arrows_in_competition(
                competition_id, athlete['athlete_id'], athlete['athlete_category'])
            for athlete in athletes
        ]
        return arrows_results

    def get_olympics_results_by_athlete(self, athlete_id, arrows=False):
        """
        For a single athlete by athlete_id,
        returns athlete bio, and all the individual and team results from each of the Olympic Games
        he took part in (as individual or within team)

        arrows: True/False
        * if True, also returns the field "arrows" with result in arrow-by-arrow form, if possible
        * if False, the field "arrows" will be None

        RETURNS:
            list() of dict()'s:
                dict:({"athlete_bio": bio, "athlete_results": athlete_results})
                    with bio of athlete in athlete_bio and list() of "results" in athlete_results
        """
        # Part 1: Get the info about athlete
        bio = self.get_athlete_biography(athlete_id)

        # Part 2: Get the info about all the athlete results
        # IndividualTeam == 0 means to get both Individual and Team results
        querystring = {"content": "ATHLETERESULTS", "Id": athlete_id, "LevelId": 1, "IndividualTeam": 0, "RBP": "All"}
        full_athlete_results = self.__get(querystring)

        athlete_results = []
        for far in full_athlete_results:
            ar = {
                    "IsTeam": far["IsTeam"],
                    "competition_id": far["Id"],
                    "name": far["Name"],
                    "category_code": far["Cat"],
                    "date": far["DFrom"],
                    "rank": far["QuRnk"],
                    "score": far["QuScore"]
            }
            if not arrows or int(far['IsTeam']):
                # if the arrows result is undesired OR if it's team score
                # provide no info
                ar['arrows'] = None
            else:
                # otherwise additionally obtain score by arrows
                arrows = self.get_athlete_arrows_in_competition(far['Id'], athlete_id, far['Cat'])
                ar['arrows'] = arrows
            athlete_results.append(ar)

        info = dict({"athlete_bio": bio, "athlete_results": athlete_results})
        return info

    def get_olympics_results_athletes(self):
        """
        For all athletes which has performed at least in 1 Olympic Games,
        returns athlete bio, and all the individual and team results from each of the Olympic Games
        he took part in (as individual or within team)

        (no arrow-by-arrow results)

        RETURNS:
            list() of list()'s (each list() is info about one athlete), and this list() is:
            list() of dict()'s:
                dict:({"athlete_bio": bio, "athlete_results": athlete_results})
                    with bio of athlete in athlete_bio and list() of "results" in athlete_results
        """
        olympic_ids = self.get_olympic_ids()

        athletes_lists = [self.get_athletes_by_competition(oid) for oid in olympic_ids]
        athletes = _unpack_list_of_lists(athletes_lists)
        athletes_ids = [a['athlete_id'] for a in athletes]
        athletes_ids = set(athletes_ids)  # leave only unique values

        infoes = [self.get_olympics_results_by_athlete(aid, arrows=False) for aid in athletes_ids]
        return infoes

    def get_country_results_in_competition(self, competition_id, country="UKR"):
        """
        For a single competition by competition_id, return list of results (one result per athlete)
        for athletes that belong to "country" country.

        Each result contain the next results within this competition:
            ['bio'] (bio of athlete)
            ['rank'] (rank athlete achieved in this competition)
            ['score'] (score athlete scored in this competition)
        """
        querystring = {"content": "INDIVIDUALQUALIFICATIONS", "CompId": competition_id, "RBP": "All"}
        items = self.__get(querystring)
        for i in range(0, len(items)):
            items[i] = [
                {
                    "athlete_id": res['Athlete']['Id'],
                    "rank": res['Rnk'],
                    "score": res['Score']
                }
                for res in items[i]['Results'] if res['Athlete']['NOC'] == country
            ]
        items = _unpack_list_of_lists(items)

        results = []
        for item in items:
            bio = self.get_athlete_biography(item['athlete_id'])
            results.append({
                'bio': bio,
                'rank': item['rank'],
                'score': item['score']
            })

        return results

    def db__get_archers(self):
        """
        Get info about all archers that took part at least in one Olympic Games

        RETURNS:
            list() of corresponding "archer" models (dictionary), ready to be written into DB
        """
        olympic_ids = self.get_olympic_ids()
        archer_ids = []
        for oid in olympic_ids:
            athletes = self.get_athletes_by_competition(oid)
            athletes = [athlete['athlete_id'] for athlete in athletes]
            archer_ids.extend(athletes)
        archer_ids = set(archer_ids)

        archers = []
        for aid in archer_ids:
            querystring = {"content": "ATHLETEBIOGRAPHY", "Id": aid}
            full_bio = self.__get(querystring)[0]
            archer = dict({
                "wa_id": full_bio["Id"],
                "name": "{0} {1}".format(full_bio["FName"], full_bio["GName"]),
                "gender": full_bio["Gender"],
                "country": full_bio["CountryShort"],
                "NOC": full_bio["NOC"],
                "age": full_bio["Age"],
                # RW or RM
                "category": "R" + full_bio["Gender"],
                # if there is current rank, assign it. If not, assign None
                "world_rank": full_bio["WorldRankings"]["Current"][0]["Rnk"] if full_bio["WorldRankings"]["Current"] else None,
            })
            archers.append(archer)

        return archers

    def db__get_single_archer(self, archer_id):
        """
        Get info about single archer by archer_id

        RETURNS:
            Corresponding "archer" model (dictionary), ready to be written into DB
        """
        querystring = {"content": "ATHLETEBIOGRAPHY", "Id": archer_id}
        full_bio = self.__get(querystring)[0]
        archer = dict({
            "wa_id": full_bio["Id"],
            "name": "{0} {1}".format(full_bio["FName"], full_bio["GName"]),
            "gender": full_bio["Gender"],
            "country": full_bio["CountryShort"],
            "NOC": full_bio["NOC"],
            "age": full_bio["Age"],
            # RW or RM
            "category": "R" + full_bio["Gender"],
            # if there is current rank, assign it. If not, assign None
            "world_rank": full_bio["WorldRankings"]["Current"][0]["Rnk"] if full_bio["WorldRankings"]["Current"] else None,
        })

        return archer

    def db__get_competitions(self):
        """
        Get info about all Olympic Games from 2000 to 2016 year

        RETURNS:
            list() of corresponding "competition" models (dictionary), ready to be written into DB
        """
        olympic_ids = self.get_olympic_ids()
        competitions = []
        for oid in olympic_ids:
            querystring = {"content": "COMPETITIONS", "CompId": oid, "RBP": "All"}
            full_info = self.__get(querystring)[0]
            competition = {
                "wa_id": full_info['ID'],
                "name": full_info['Name'],
                "date": full_info['DFrom'],
                "level": full_info['ComLevel'],
                "sub_level": full_info['ComSubLevel'],
            }
            competitions.append(competition)

        return competitions

    def db__get_qualifications(self):
        """
        Get info about all qualifications shot in Olympic Games 2000-2016

        IMPORTANT NOTE:
        To fill "qualifications" collection, it is assumed that
        "archers" and "competition" collections are already formed.

        RETURNS:
            list() of corresponding "qualification" models (dictionary), ready to be written into DB
        """
        olympic_ids = self.get_olympic_ids()
        qualifications = []
        for oid in olympic_ids:
            querystring = {"content": "INDIVIDUALQUALIFICATIONS", "CompId": oid, "RBP": "All"}
            individual_qualifications_categories = self.__get(querystring)
            for iqc in individual_qualifications_categories:
                category = iqc['Code']
                for iq in iqc['Results']:
                    qualifications.append({
                        "category": category,
                        "rank": iq['Rnk'],
                        "score": iq['Score'],
                        "is_team": 0,
                        "archer_ids": [int(iq['Athlete']['Id'])],
                        "competition_id": oid,
                    })
            querystring = {"content": "TEAMQUALIFICATIONS", "CompId": oid, "CatCode": "RM|RW", "RBP": "All"}
            team_qualifications_categories = self.__get(querystring)
            for tqc in team_qualifications_categories:
                category = tqc['Code']
                for tq in tqc['Results']:
                    qualifications.append({
                        "category": category,
                        "rank": tq['Rnk'],
                        "score": tq['Score'],
                        "is_team": 1,
                        "archer_ids": [int(member['Id']) for member in tq['Members']],
                        "competition_id": oid,
                    })

        return qualifications

    def db__get_qualifications_arrows(self, qualifications_from_db):
        """
        IMPORTANT NOTE:
        To fill "qualification arrows" collection, it is assumed that
        "qualifications" collection is already formed.

        1. Call get_qualifications(individual_team=1) from MongoManage() (mm) and receive "qualifications_from_db"
        2. For each qualification from qualifications_from_db (individual qualification round),
        Try to find the detailed information: i.e. info about every shot from 72 shots
        made within Qualification Round

        RETURNS:
            list() of corresponding "qualifications_arrows" models (dictionary), ready to be written into DB
        """

        qualifications_arrows = []

        for q in qualifications_from_db:
            arrows = self.get_athlete_arrows_in_competition(q['competition_id'], q['archer_ids'][0], q['category'])
            if arrows:
                qualifications_arrows.append({
                    "qualification_id": q['_id'],
                    "arrows": arrows,
                })

        return qualifications_arrows
