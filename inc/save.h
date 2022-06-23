/**
 * Copyright, 2022.
 * This file is 
 * Author: Changhyun Son <xoowoo35@gmail.com>
*/

#include <AclRedisClient.h>
#include <json/json.h>
#include <dlib/server.h>
#include <dlib/threads.h>
#include <dlib/iosockstream.h>
#include <dlib/sockets.h>
#include <db_wrapper.h>
#include <RegularDbItems.hpp>
#include <sys/shm.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vsys.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "data.h"

using namespace std;

class Login
{
  v::db::DBWrapper db_client;
  std::string key_user_id = regularDbItemKeys::fifa::USER_ID;
  std::string key_user_inf = regularDbItemKeys::fifa::USER_INF;
public:
  int GetUserId();
  RpnsStyle1 SignUpParse(const dlib::incoming_things& incoming);
  void DBUserId(int user_id);
  void DBUserInf(UserInf user_inf);
  bool LoginParse(const dlib::incoming_things& incoming);
  bool CheckingID(std::vector<UserInf> vec_user_inf, string user_email, string user_passward);
  bool CheckingPW(string get_passward, string user_passward);

  bool CheckingOverlapEmail(string queries);
  bool CheckingPassward(string queries);
  std::string LocalChangeTime();
};