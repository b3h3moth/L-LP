#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <errno.h>
#include "user_group_conversions.h"

// Converte user ID in user name
char *username_from_userid(uid_t uid) {
    struct passwd *pwd;

    pwd = getpwuid(uid);
    if (pwd == NULL) {
        if (errno == 0) {
            fprintf(stderr, "Account Not Found.\n");
            return NULL;
        } else {
            fprintf(stderr, "Err. getpwuid() Failed.\n");
            return NULL;
        }
    } else
        return pwd->pw_name;
}

// Converte user name in user ID
uid_t userid_from_username(const char *username) {
    struct passwd *pwd;

    if (username == NULL || username == '\0')
        return -1;

    pwd = getpwnam(username);
    if (pwd == NULL) {
        if (errno == 0) {
            fprintf(stderr, "Account Not Found.\n");
            return -1;
        } else {
            fprintf(stderr, "Err. getpwnam() Failed.\n");
            return -1;
        }
    } else
        return pwd->pw_uid;
}

// Converte Group ID in group name
char *groupname_from_groupid(gid_t gid) {
    struct group *grp;

    grp = getgrgid(gid);
    if (grp == NULL) {
        if (errno == 0) {
            fprintf(stderr, "Account Not Found.\n");
            return NULL;
        } else {
            fprintf(stderr, "Err. getgrgid() Failed.\n");
            return NULL;
        }
    } else
        return grp->gr_name;
}

// Converte group name in Group ID
gid_t groupid_from_groupname(const char *groupname) {
    struct group *grp;

    if (groupname == NULL || groupname == '\0')
        return -1;

    grp = getgrnam(groupname);
    if (grp == NULL) {
        if (errno == 0) {
            fprintf(stderr, "Account Not Found.\n");
            return -1;
        } else {
            fprintf(stderr, "Err. getgrnam() Failed.\n");
            return -1;
        }
    } else
        return grp->gr_gid;
}
