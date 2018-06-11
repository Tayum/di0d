# -*- coding: utf-8 -*-
"""
Much Obliged to World Archery © for providing me with the info about Athletes and Competitions
within Archery World.
"""
from time import sleep

import numpy as np
import scipy as sp
import pandas as pd
import matplotlib.pyplot as plt

from wa_api import WA_API
from mongomanage import MongoManage

# Some default values for the statistics functions below
COMPETITION_ID = 14870  # Rio 2016 Olympic Games
ARCHER_ID = 5107  # Brady Ellison
COUNTRY_NOC = "UKR"  # NOC stands for National Olympic Committee

# Init the Global Variables
wa_api = WA_API()
# mm = MongoManage(port=27001, rs='wa0')
mm = MongoManage(port=27017)
# sleep for Mongo to establish connection
sleep(0.1)
mm.set_database()


class FillDB:
    """
    Class that uses both World Archery API class
    and DB class to take the data from World Archery API
    and fill the DB with this data.
    """
    @staticmethod
    def fill_archers_collection():
        archers = wa_api.db__get_archers()
        for a in archers:
            _id = mm.insert("archers", a)

    @staticmethod
    def fill_competitions_collection():
        competitions = wa_api.db__get_competitions()
        for c in competitions:
            _id = mm.insert("competitions", c)

    @staticmethod
    def fill_qualifications_collection():
        qualifications = wa_api.db__get_qualifications()
        for q in qualifications:
            _id = mm.insert_qualification(q)

    @staticmethod
    def fill_qualifications_arrows_collection():
        qualifications = mm.get_qualifications(individual_team=1)
        qualifications_arrows = wa_api.db__get_qualifications_arrows(qualifications)
        for qa in qualifications_arrows:
            _id = mm.insert("qualifications_arrows", qa)


class Menu:
    """
    Class that handles the interaction with user,
    interacts with DB,
    forms statistics and prints it to user
    """
    @staticmethod
    def __arrows_percentage(competition_wa_id):
        arrows = mm.get_arrows_within_competition(competition_wa_id)
        arrows_series = pd.Series(arrows)
        arrows_amount = arrows_series.value_counts()
        arrows_percentage = arrows_series.value_counts(normalize=True)

        arrow_result = ['X']
        arrow_result.extend([str(i) for i in range(10, 0, -1)])
        arrow_result.append('M')

        print("Arrow\tAmount   \tPercentage")
        for ar in arrow_result:
            if ar in arrows_amount and ar in arrows_percentage:
                print("{0}\t\t{1}   \t\t{2:.4f}".format(ar, arrows_amount[ar], arrows_percentage[ar] * 100))
            else:
                print("{0}\t\t{1}   \t\t{2}".format(ar, 0, 0))

    @staticmethod
    def __mean_results():
        competitions = mm.get_competitions()
        for c in competitions:
            print("\n====={0}=====".format(c['name']))
            qualifications = mm.get_individual_qualification_scores_within_competition(c['wa_id'])
            df = pd.DataFrame(qualifications)
            print("Men AVG: " + str(df['score'][df['category'] == 'RM'].mean()))
            print("Women AVG: " + str(df['score'][df['category'] == 'RW'].mean()))

    @staticmethod
    def __max_result():
        max_scores = mm.get_maximum_individual_qualification_score()
        male = max_scores['male']
        female = max_scores['female']
        print("Male score (by {0} (Age: {1}, representing {2}) within {3}): {4}".format(
            male['archer_ids']['name'],
            male['archer_ids']['age'],
            male['archer_ids']['country'],
            male['competition_id']['name'],
            male['score'],
        ))
        print("Female score (by {0} (Age: {1}, representing {2}) within {3}): {4}".format(
            female['archer_ids']['name'],
            female['archer_ids']['age'],
            female['archer_ids']['country'],
            female['competition_id']['name'],
            female['score'],
        ))

    @staticmethod
    def __archer_results(archer_wa_id):
        info = mm.get_archer_results(archer_wa_id)
        archer = info['archer']
        print("\n=====ARCHER BIO=====")
        print("Name: {0}\nGender: {1}\nCountry: {2}\nAge: {3}\nWorld Rank: {4}".format(
            archer['name'],
            archer['gender'],
            archer['country'],
            archer['age'],
            archer['world_rank'] if archer['world_rank'] else "Unranked",
        ))
        print("====================")

        results = info['qualifications']
        df = pd.DataFrame(results)
        print("=====RESULTS=====")
        for index, result in df.iterrows():
            print("* {0}: Ranked [{1}] with {2} Points (as {3})".format(
                result['competition_id']['name'],
                result['rank'],
                result['score'],
                ["Individual", "Team"][result['is_team']],
            ))
        print("=================")

    @staticmethod
    def __country_results(NOC):
        results = mm.get_country_results(NOC)
        df = pd.DataFrame(results)
        print("=====RESULTS=====")
        for index, result in df.iterrows():
            print("* {0}: Ranked [{1}] with {2} Points ({3})".format(
                result['competition_id']['name'],
                result['rank'],
                result['score'],
                ", ".join([a['name'] for a in result['archers']]),
            ))
        print("=================")

    @staticmethod
    def __print_help():
        print("-h or --help to print this help")
        print("-q or --quit to quit")
        print("--arrows <competition_id> for displaying info about arrows within single competition"
              "\n * (<competition_id> == 14870 is the only available ID at this moment)")
        print("--mean for displaying mean results (Men / Women) within all available competitions")
        print("--max for displaying max results (Men / Women) within all available competitions")
        print("--archer <archer_id> for displaying results of archer within all available competitions")
        print("--country <NOC code> for displaying results of country within all available competitions")

    def init_menu(self):
        print("Type -h or --help for printing help")
        while True:
            choice = input("> ").strip()
            try:
                if choice == "-q" or choice == "--quit":
                    break

                elif choice == "-h" or choice == "--help":
                    self.__print_help()

                elif "--arrows" in choice:
                    try:
                        competition_id = int(choice.replace("--arrows", "").strip())
                    except ValueError:
                        competition_id = COMPETITION_ID
                    self.__arrows_percentage(competition_id)

                elif "--mean" == choice:
                    self.__mean_results()

                elif "--max" == choice:
                    self.__max_result()

                elif "--archer" in choice:
                    try:
                        archer_id = int(choice.replace("--archer", "").strip())
                    except ValueError:
                        archer_id = ARCHER_ID
                    self.__archer_results(archer_id)

                elif "--country" in choice:
                    country_noc = choice.replace("--country", "").strip()
                    if not country_noc:
                        country_noc = COUNTRY_NOC
                    self.__country_results(country_noc)
            except:
                print("Something went wrong while processing your request.")


if __name__ == '__main__':
    # fdb = FillDB()
    # fdb.fill_archers_collection()
    # fdb.fill_competitions_collection()
    # fdb.fill_qualifications_collection()
    # fdb.fill_qualifications_arrows_collection()

    # menu = Menu()
    # menu.init_menu()
    print("\n\nI'm done")
