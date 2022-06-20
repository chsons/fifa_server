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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "data.h"


class Login
{
  v::db::DBWrapper db_client;

public:
  int GetUserId();
  void SignUpParse(const dlib::incoming_things& incoming);
  void DBUserId(int user_id);
  vodi DBUserInf(UserInf user_inf);
  string LocalChangeTime();
}