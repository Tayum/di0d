#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <libxml/parser.h> // !!!
#include <libxml/tree.h> // !!!

#include "investors.h"

struct identifier_s {
	char name[20];
	char nickname[20];
	char surname[30];
};

typedef struct identifier_s identifier_t;

struct investor_s {
	identifier_t id;
	double rating;
	struct tm firstInv;
	int exp;
	int moneyInv;
	char curInv[30];
};

investor_t * investor_parse(investor_t * investor, xmlNode * curNode);
void identifier_parse(identifier_t * identifier, xmlNode * curNode);

// Constructor for investor
investor_t * investor_new(void) {
	investor_t * investorSmp = malloc(sizeof(investor_t));
	// id struct
	strcpy(investorSmp->id.name, "NoName");
	strcpy(investorSmp->id.nickname, "NoNickname");
	strcpy(investorSmp->id.surname, "NoSurname");
	// rating
	investorSmp->rating = 0.0;
	// firstInv date
	memset(&investorSmp->firstInv, 0, sizeof(investorSmp->firstInv));
	investorSmp->firstInv.tm_year = 1900;
	investorSmp->firstInv.tm_mday = 01;
	investorSmp->firstInv.tm_mon = 01;
	// exp
	investorSmp->exp = 0;
	// moneyInv
	investorSmp->moneyInv = 0;
	// curInv
	strcpy(investorSmp->curInv, "NoCurInv");
	return investorSmp;
}

// Destructor for investor
void investor_delete(investor_t * investor) {
	free(investor);
}

// Parse for investor array from file
void investor_ParseXML(investor_t ** investorArr, const char * fileNameXML) {
	xmlDoc * xDoc = xmlReadFile(fileNameXML, "UTF-8", 0);
	if (xDoc == NULL) {
		puts("\nFile with such name does not exist.");
		xmlFreeDoc(xDoc);
	}
	else {
		xmlNode * xRootEl = xmlDocGetRootElement(xDoc);
		xmlNode * curNode;
		int i = 0;
		for (curNode = xRootEl->children; curNode != NULL; curNode = curNode->next) {
			if (xmlStrEqual(curNode->name, "investor")) {
				investor_parse(investorArr[i], curNode);
				i++;
			}
		}
		xmlFreeDoc(xDoc);
	}
}

// Parse investor (of the investor array)
investor_t * investor_parse(investor_t * investor, xmlNode * curNode) {
	char * buff;
	for (curNode = curNode->children; curNode != NULL; curNode = curNode->next) {
		// Get identifier struct (name,nickname,surname)
		if (xmlStrEqual(curNode->name, "identifier"))
		{
			identifier_parse(&(investor->id), curNode);
		}
		// Get rating
		else if (xmlStrEqual(curNode->name, "rating")) {
			buff = xmlNodeGetContent(curNode);
			investor->rating = atof(buff);
		}
		// Get firstInv date
		else if (xmlStrEqual(curNode->name, "firstInvestmentDate")) {
			buff = xmlNodeGetContent(curNode);
			sscanf(buff, "%d-%d-%d", &investor->firstInv.tm_year, &investor->firstInv.tm_mday, &investor->firstInv.tm_mon);
		}
		// Get exp
		else if (xmlStrEqual(curNode->name, "experienceYears")) {
			buff = xmlNodeGetContent(curNode);
			investor->exp = atoi(buff);
		}
		// Get moneyInv
		else if (xmlStrEqual(curNode->name, "totalMoneyInvested")) {
			buff = xmlNodeGetContent(curNode);
			investor->moneyInv = atoi(buff);
			// Get curInv attr
			buff = xmlGetProp(curNode, "curInvest");
			strcpy(investor->curInv, buff);
		}
	}
	xmlFree(buff);
	return investor;
}

// Parse identifier (of the investor)
void identifier_parse(identifier_t * identifier, xmlNode * curNode) {
	char * buff;
	for (curNode = curNode->children; curNode != NULL; curNode = curNode->next) {
		// Get name
		if (xmlStrEqual(curNode->name, "name")) {
			buff = xmlNodeGetContent(curNode);
			strcpy(identifier->name, buff);
		}
		// Get nickname
		else if (xmlStrEqual(curNode->name, "nickname")) {
			buff = xmlNodeGetContent(curNode);
			strcpy(identifier->nickname, buff);
		}
		// Get surname
		else if (xmlStrEqual(curNode->name, "surname")) {
			buff = xmlNodeGetContent(curNode);
			strcpy(identifier->surname, buff);
		}
	}
}

// Print for investor
void investor_print(investor_t * investor) {
	puts("==========INVESTOR==========");
	printf("Name: %s \"%s\" %s\n", investor->id.name, investor->id.nickname, investor->id.surname);
	printf("Rating: %.1f\n", investor->rating);
	printf("First invention made on %d-%d-%d\n", investor->firstInv.tm_year, investor->firstInv.tm_mon, investor->firstInv.tm_mday);
	printf("Years of experience: %d\n", investor->exp);
	printf("Total money invested: %d$\n", investor->moneyInv);
	printf("Current investment project: %s\n", investor->curInv);
	puts("============================\n");
}