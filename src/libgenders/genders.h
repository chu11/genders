/*
 * $Id: genders.h,v 1.18 2003-04-18 19:46:48 achu Exp $
 * $Source: /g/g0/achu/temp/genders-cvsbackup-full/genders/src/libgenders/genders.h,v $
 */

#ifndef _GENDERS_H
#define _GENDERS_H

#include <stdio.h>

/******************
 * defines        *
 ******************/

/* genders error codes */
#define GENDERS_ERR_SUCCESS       0 /* success */
#define GENDERS_ERR_NULLHANDLE    1 /* genders handle is null */
#define GENDERS_ERR_OPEN          2 /* could not open file (errno valid) */
#define GENDERS_ERR_READ          3 /* could not read file (errno valid) */
#define GENDERS_ERR_PARSE         4 /* parse error on genders file */
#define GENDERS_ERR_NOTOPEN       5 /* genders file not open */
#define GENDERS_ERR_NOTCLOSED     6 /* genders file is not closed */
#define GENDERS_ERR_OVERFLOW      7 /* array is not big enough for result */
#define GENDERS_ERR_PARAMETERS    8 /* incorrect parameters passed in */
#define GENDERS_ERR_NULLPTR       9 /* null pointer in list */
#define GENDERS_ERR_NOTFOUND     10 /* node not found */
#define GENDERS_ERR_OUTMEM       11 /* out of memory */
#define GENDERS_ERR_FREEMEM      12 /* memory has not been freed */
#define GENDERS_ERR_ISFREE       13 /* memory is already free */
#define GENDERS_ERR_MAGIC        14 /* magic number incorrect */
#define GENDERS_ERR_INTERNAL     15 /* internal system error */
#define GENDERS_ERR_ERRNUMRANGE  16 /* error number out of range */

/*
 * review: autoconfiscate these values:
 */
#define DEFAULT_GENDERS_FILE        "/etc/genders"

typedef struct genders *genders_t;

/******************
 * API            *
 ******************/

/* Creates & Initializes a genders handle 
 * Returns: NULL on memory allocation error
 */
genders_t genders_handle_create(void);

/* Destroys a genders handle.
 * Returns: 0 on success, -1 on failure.
 */
int genders_handle_destroy(genders_t handle);

/* Opens/reads/parses the specified genders file and associates it
 * with a handle.
 * If filename is NULL, attempts to read default genders file
 * Returns: 0 on success, -1 on failure.  
 */
int genders_load_data(genders_t handle, const char *filename);

/* Closes the genders file associated with handle and frees cached
 * data.
 * Returns: 0 on success, -1 on failure.  
 */
int genders_close(genders_t handle);

/* Returns an error code associated with a handle 
 */
int genders_errnum(genders_t handle);

/* Translates a genders error code to a text message.  
 * Returns: pointer to NUL-terminated statically allocated string.
 */
char *genders_strerror(int errnum);

/* Returns a string describing the most recent error that occurred.
 */
char *genders_errormsg(genders_t handle);

/* Produces a message on standard error describing the most recent
 * error that occurred.  
 */
void genders_perror(genders_t handle, const char *msg);

/* Dumps the genders file stored in the handle to the file stream.
 * If stream is NULL, dumps to stdout.
 * Returns: 0 on success, -1 on failure 
 */
int genders_handle_dump(genders_t handle, FILE *stream);

/* Get the number of nodes read from the genders file
 * Returns: number of nodes on success, -1 on failure 
 */
int genders_getnumnodes(genders_t handle);

/* Get the number of attributes read from the genders file
 * Returns: number of attributes on success, -1 on failure 
 */
int genders_getnumattrs(genders_t handle);

/* Get the max number of attributes read of any one node in the
 * genders file
 * Returns: number of attributes on success, -1 on failure 
 */
int genders_getmaxattrs(genders_t handle);

/* Get the max node name length of any one node in the genders file
 * Returns: maximum node length on success, -1 on failure 
 */
int genders_getmaxnodelen(genders_t handle);

/* Get the max attribute name length of any one node in the genders
 * file
 * Returns: maximum attribute length on success, -1 on failure 
 */
int genders_getmaxattrlen(genders_t handle);

/* Get the max value length of any one attribute in the genders file
 * Returns: maximum value length on success, -1 on failure 
 */
int genders_getmaxvallen(genders_t handle);

/* Allocate an array of character strings to store node names in.
 * Returns: number of elements the list can store on succcess,
 *          -1 on failure
 */
int genders_nodelist_create(genders_t handle, char ***nodelist);

/* Clears the data stored in a previously created node list
 * Returns: 0 on success, -1 on failure
 */
int genders_nodelist_clear(genders_t handle, char **nodelist);

/* Frees memory of a previously created node list
 * Returns: 0 on success, -1 on failure
 */
int genders_nodelist_destroy(genders_t handle, char **nodelist);

/* Allocate an array of character strings to store attribute names in.
 * Returns: number of elements the list can store on succcess,
 *          -1 on failure
 */
int genders_attrlist_create(genders_t handle, char ***attrlist);

/* Clears the data stored in a previously created attribute list
 * Returns: 0 on success, -1 on failure
 */
int genders_attrlist_clear(genders_t handle, char **attrlist);

/* Frees memory of a previously created attribute list
 * Returns: 0 on success, -1 on failure
 */
int genders_attrlist_destroy(genders_t handle, char **attrlist);

/* Allocate an array of character strings to store values in.
 * Returns: number of elements the list can store on succcess,
 *          -1 on failure
 */
int genders_vallist_create(genders_t handle, char ***vallist);

/* Clears the data stored in a previously created value list
 * Returns: 0 on success, -1 on failure
 */
int genders_vallist_clear(genders_t handle, char **vallist);

/* Frees memory of a previously created value list
 * Returns: 0 on success, -1 on failure
 */
int genders_vallist_destroy(genders_t handle, char **vallist);

/* Get the name of the current node (node name is the shortened
 * hostname).
 * Returns: 0 on success, -1 on failure 
 */
int genders_getnodename(genders_t handle, char *node, int len);

/* Gets list of nodes with the specified attribute.  
 * If attr is NULL, gets all nodes.  
 * If val is non-NULL, get only nodes with attributes=val.
 * Nodes are returned in genders file order.
 * Returns: number of matches on success, -1 on failure.
 */
int genders_getnodes(genders_t handle, 
                     char *nodes[], 
                     int len, 
                     const char *attr, 
                     const char *val);

/* Gets list of attributes for the specified node.  
 * If node is NULL, gets all attributes for the current node.  
 * If vals array is non-NULL, stores any attribute values in it.
 * Returns: number of matches on success, -1 on failure.
 */
int genders_getattr(genders_t handle, 
                    char *attrs[], 
                    char *vals[], 
                    int len, 
                    const char *node);

/* Gets all attributes stored in the genders file
 * Returns: number of attributes on success, -1 on failure
 */
int genders_getattr_all(genders_t handle, char *attrs[], int len);

/* Gets the value of an attribute from a node
 * If node is NULL, uses the current node.  
 * Returns: 1 if attr found, 0 if attr not found, -1 on failure.
 */
int genders_getattrval(genders_t handle, 
		       const char *node, 
		       const char *attr, 
		       char *val, 
		       int len);

/* Tests whether node has an attribute, or attribute=value pair
 * If node is NULL, tests the current node.
 * If val is NULL, only the attribute is tested
 * Returns: 1=true , 0=false, -1=failure.
 */
int genders_testattrval(genders_t handle, 
                        const char *node, 
                        const char *attr, 
                        const char *val);

/* Tests whether the node exists in the genders file
 * If node is NULL, tests the current node.
 * Returns: 1=true , 0=false, -1=failure.
 */
int genders_testnode(genders_t handle, const char *node);

/* Parses a genders file, and outputs parse debugging 
 * information to the file stream.  
 * if filename is NULL, parses default genders file.
 * if stream is NULL, outputs to stderr
 * Returns the number of parse errors (0 if no parse errors), -1 on error
 */
int genders_parse(genders_t handle, const char *filename, FILE *stream);

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */

#endif /* _GENDERS_H */
