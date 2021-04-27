#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"

/*----------------------------------------------------------------------
Uncomment and use the following code if you want*/

#define UNIT_ARRAY_SIZE 1024

struct UserInfo {
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
};

struct DB {
  struct UserInfo *pArray;   // pointer to the array
  int curArrSize;            // current array size (max # of elements)
  int numItems;              // # of stored items, needed to determine
			     // # whether the array should be expanded
			     // # or not
};
enum {HASH_MULTIPLIER = 65599};

static int hash_function(const char *pcKey, int iBucketCount)

/* Return a hash code for pcKey that is between 0 and iBucketCount-1,
   inclusive. Adapted from the EE209 lecture notes. */
{
   int i;
   unsigned int uiHash = 0U;
   for (i = 0; pcKey[i] != '\0'; i++)
      uiHash = uiHash * (unsigned int)HASH_MULTIPLIER
               + (unsigned int)pcKey[i];
   return (int)(uiHash % (unsigned int)iBucketCount);
}

enum {BUCKET_COUNT = 1024};

struct Node {
   const char *key;
   int value;
   struct Node *next;
};

struct Table {
   struct Node *array[BUCKET_COUNT];
};

struct Table *Table_create(void) {
   struct Table *t;
   t = (struct Table*)calloc(1, sizeof(struct Table));
   return t;
}
struct Table *t;

t = Table_create();



/*----------------------------------------------------------------------*/
char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;      }                      // Return the new string 
int search_name(DB_T d, const char *pvSoughtElement)
{
    int i;
    //printf("%d",d->numItems);
    for (i = 0; i < (d->numItems); i++)
        if (strcmp(d->pArray[i].name, pvSoughtElement) == 0)
            return i; /* Element found */
    
    return -1; /* Element not found */
}
int search_id(DB_T d, const char *pvSoughtElement)
{
    int i;
    for (i = 0; i < d->numItems; i++)
        if (strcmp(d->pArray[i].id, pvSoughtElement) == 0)
            return i; /* Element found */

    return -1; /* Element not found */
}

/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void)
{
  /* Uncomment and use the following implementation if you want*/
  DB_T d;
  
  d = (DB_T) calloc(1, sizeof(struct DB));
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }
  d->curArrSize = UNIT_ARRAY_SIZE; // start with 1024 elements
  d->pArray = (struct UserInfo *)calloc(d->curArrSize,
               sizeof(struct UserInfo));
  d->numItems=0;//i added this 
  if (d->pArray == NULL) {
    fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	    d->curArrSize);   
    free(d);
    return NULL;
  }
  return d;

}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  /* fill out this function */
  if(d == NULL)
    {
        return ;
    }
    else
    {
        free(d->pArray);
        free(d); }

  //assert(0);
  //return NULL;
}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
		 const char *name, const int purchase)
{
  /* fill out this function */
  if (d==NULL||id==NULL||name==NULL||purchase<=0){
     return -1;
  }

  if ((search_name(d,name) != -1) || (search_id(d,id) != -1)) {
    return -1;
  }
  //assert(0);
  else{
   int P=d->numItems;
   d->pArray[P].name=strdup(name);
   d->pArray[P].id=strdup(id);
   d->pArray[P].purchase=purchase;
   (d->numItems)+=1;
   printf("%d",d->numItems);
  return 0;}
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  /* fill out this function */
  //assert(0);
  int i,iIndex;
  //assert(d!= NULL); 
  if ((iIndex=search_id(d,id))!= -1 ){
    d->numItems--;
    //int iIndex=search_id(d,id);
    //assert(iIndex >= 0);       
    /* Pull position of all elements after iIndex by one */
    //if (iIndex==0){return 0;}
    for (i = iIndex; i < d->numItems; i++)
        d->pArray[i] = d->pArray[i+1];
    printf("%d",d->numItems);
    return 0;}
  else { printf("%s","loop");
  return (-1);}
}

/*--------------------------------------------------------------------*/
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  /* fill out this function */
  //assert(0);
  int i,iIndex;
  if ((iIndex=search_name(d,name))!=(-1)){ 
    d->numItems--;
    //assert(iIndex >= 0);       
    /* Pull position of all elements after iIndex by one */
    //if (iIndex==0)return 0;
    for (i = iIndex; i < d->numItems; i++)
        d->pArray[i] = d->pArray[i+1];
    printf("%d",d->numItems);
    return 0;}
  else { printf("%s","lop");
  return (-1);}
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  /* fill out this function */
  //if d or id is NULL, it is a failure.
  assert(d!=NULL); 
  assert(id!=NULL);
  int iIndex;
  //if name found,returns purchase else returns -1
  if ((iIndex=search_id(d,id))!=(-1)){ 
    return (d->pArray[iIndex].purchase);}
  else
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByName(DB_T d, const char* name)
{
  /* fill out this function */
  //if d or id is NULL, it is a failure.
  assert(d!=NULL);
  assert(name!=NULL);
  int iIndex;
  //if name found,returns purchase else returns -1
  if ((iIndex=search_name(d,name))!=(-1)){ 
    return (d->pArray[iIndex].purchase);}
  else
  return -1;
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  /* fill out this function */
  
  if (d==NULL|| fp==NULL)return (-1);
  int i=0;
  int value=0;
  if (5==5){
     while (i < (d->numItems)){
       value+= fp(d->pArray[i].id, d->pArray[i].name ,d->pArray[i].purchase);i++;}}
  return value;

  /*
  if (fpFUNCPTR_T NameStartsWithA){
     while (i < (d->numItems)){
        if (GetPurchaseByName(d,d->pArray[i].name)!=-1);
           value+=GetPurchaseByName(d,d->pArray[i].name);
        i++;}}
  return value;
  
  if (fp==NameStartsWithA)printf("%s","hoo000");
  if (fp==NameStartsWithA)printf("%s","hoo999o");*/
  //assert(0);
  // return 0;
 
}
