/**
 * Copyright, 2022.
 * This file is 
 * Author: Changhyun Son <xoowoo35@gmail.com>
*/

typedef struct _UserInf{
  int id;        // db_id
  char email[36];     // login_id
  char username[16];
  char passward[36];
  bool verified;
  uint64_t last_login;
  bool is_active;
  bool is_superuser;
  bool is_staff;

}UserInf;


typedef struct _RpnsStyle1{
  bool success;
  int result;
}RpnsStyle1;
