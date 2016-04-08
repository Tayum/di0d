#ifndef INVESTORS_H_INCLUDED
#define INVESTORS_H_INCLUDED

typedef struct investor_s investor_t;

investor_t * investor_new(void);
void investor_delete(investor_t * investor);
void investor_ParseXML(investor_t ** investorArr, const char * fileNameXML);
void investor_print(investor_t * investor);

#endif //INVESTORS_H_INCLUDED