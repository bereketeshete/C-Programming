#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"

/*----------------------------------------------------------------------
Uncomment and use the following code if you want



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

----------------------------------------------------------------------*/
#define UNIT_ARRAY_SIZE 1024

enum {BUCKET_COUNT = 1024};
enum {HASH_MULTIPLIER = 65599};

struct Node {
   char *name;
   char *id;
   int purchase;
   struct Node *next_id;
   struct Node *next_name;
   struct Node *previous_id;
   struct Node *previous_name;
};


struct DB {
   struct Node *hashId[BUCKET_COUNT];
   struct Node *hashName[BUCKET_COUNT];
   int id_bucket;
   int name_bucket;
   int id_items;
   int name_items;
};
// strdup function
char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);    
    return d;   }                 // Copy the characters



// hash function
static int hash(const char *pcKey, int iBucketCount)

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

// search for id
int search_id(DB_T d, const char *id) 
{
   struct Node *p;
   int h = hash(id,d->id_bucket);
   for (p = d->hashId[h]; p != NULL; p = p->next_id){
      if (strcmp(p->id, id) == 0) {
         return 0;
      };}
   return -1;
}
// search for name
int search_name(DB_T d, const char *name) 
{
   struct Node *p;
   int h = hash(name,d->name_bucket);
   for (p = d->hashName[h]; p != NULL; p = p->next_name){
      if (strcmp(p->name, name) == 0) {
         return 0;
      };}
   return -1;
}


/////////////////////////
struct Node *ListDelete(struct Node* currP,const char* id)
{
  /* See if we are at end of list. */
  
  if (currP == NULL)
    return NULL;
  int k=strcmp(currP->id,id);
  if (k==0) {
    struct Node *tempNextP;

    /* Save the next pointer in the node. */
    tempNextP = currP->next_id;
    printf("%s","pol");
    /* Deallocate the node. */
    free(currP);

    return tempNextP;
  }
  currP->next_id = ListDelete(currP->next_id, id);
  return currP;
}


/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void)
{
  DB_T d;
  d = (DB_T)calloc(1, sizeof(struct DB));
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;}
  d->id_bucket = UNIT_ARRAY_SIZE; // start with 1024 elements
  d->name_bucket = UNIT_ARRAY_SIZE; // start with 1024 elements
  // intialize two hash tables
  /*d->hashId = (struct Node *)calloc(1,
               sizeof(struct Node));
  if (d->hashId == NULL) {
    fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	    d->id_bucket);   
    free(d);
    return NULL;
  }
  d->hashName = (struct Node *)calloc(1,
               sizeof(struct Node));
  if (d->hashName == NULL) {
    fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	    d->name_bucket);   
    free(d);
    return NULL;}*/
  
  return d;
  
}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  /* fill out this function */
  free(d);
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
  if ((search_id(d,id)==0)||(search_name(d,name)==0) ){return -1;}
  struct Node *p = (struct Node*)malloc(sizeof(struct Node));
   int hid = hash(id,d->id_bucket);
   int hname = hash(name,d->name_bucket);
   p->name = strdup(name);
   p->id = strdup(id);
   p->purchase=purchase;
   p->next_id = d->hashId[hid];
   p->next_name = d->hashName[hname]; 
   d->hashId[hid] = p;
   d->hashName[hname] = p;
  //assert(0);
  return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  /* fill out this function */
  //struct Node *p;
  struct Node *temp;
  int h = hash(id,d->id_bucket);
  printf("%s  %s",d->hashId[h]->id, id);
  if (strcmp(d->hashId[h]->id,id)==0){ printf("%s","hoom");
       temp=d->hashId[h];
       d->hashId[h]=d->hashId[h]->next_id;
       free(temp);
       return 0;}
  /*
  for (p = d->hashId[h]; p != NULL; p = p->next_id){ 
      if (strcmp(p->id, id) == 0) {;
         return 0;
      };}*/   
  //assert(0);
  return (-1);
}

/*--------------------------------------------------------------------*/
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  /* fill out this function */
  struct Node *temp;
  int h = hash(name,d->name_bucket);
  printf("%s  %s",d->hashName[h]->id, id);
  if (strcmp(d->hashId[h]->id,id)==0){ printf("%s","hoom");
       temp=d->hashId[h];
       d->hashId[h]=d->hashId[h]->next_id;
       free(temp);
       return 0;}
   return -1;
  //assert(0);
  
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  /* fill out this function */
  struct Node *p;
   int h = hash(id,d->id_bucket);
   for (p = d->hashId[h]; p != NULL; p = p->next_id){
      if (strcmp(p->id, id) == 0) {
         return p->purchase;
      };}
  return -1;
  //assert(0);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByName(DB_T d, const char* name)
{
  /* fill out this function */
  // finds matching name from hashName hash and returns its purchase
  struct Node *p;
  int h = hash(name,d->name_bucket);
  for (p = d->hashName[h]; p != NULL; p = p->next_name){
      if (strcmp(p->name, name) == 0) {
         return p->purchase;
      };}
   
  //assert(0);
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  /* fill out this function */
  int b=0;
  int value=0;
  if (d==NULL|| fp==NULL)return (-1);
  struct Node *p;
  struct Node *nextp;
  for (b = 0; b < (d->id_bucket); b++)
     for (p = d->hashId[b]; p != NULL; p = nextp) {
         nextp = p->next_id;
         value+= fp(p->id, p->name ,p->purchase);}
  //assert(0);
  return value;
}



