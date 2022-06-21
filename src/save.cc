/**
 * Copyright, 2022.
 * This file is 
 * Author: Changhyun Son <xoowoo35@gmail.com>
*/
#include "save.h"

int Login::GetUserId()
{
  std::vector<int> ret_user_id;
  std::string get_key = regularDbItemKeys::fifa::USER_ID;
  if(db_client.GetListData<int>(
        get_key, ret_user_id) != db_client.kSuccess)
  {
    LOG(ERROR) << "GetListData: It can't find the key about USER_INF";
  }

  return ret_user_id.size();
}
void Login::DBUserId(int user_id)
{
  std::string get_key = regularDbItemKeys::fifa::USER_ID;
  if(db_client.PushDataOnList<int>
        (get_key, user_id) != db_client.kSuccess ) 
  {
    LOG(ERROR) << "PushDataOnList: It can't find the key about USER_ID";
  }
}
void Login::DBUserInf(UserInf user_inf)
{
  std::string get_key = regularDbItemKeys::fifa::USER_INF;
  if(db_client.PushDataOnList<UserInf>
        (get_key, user_inf) != db_client.kSuccess ) 
  {
    LOG(ERROR) << "PushDataOnList: It can't find the key about USER_INF";
  }
}
void Login::SignUpParse(const dlib::incoming_things& incoming)
{
  UserInf user_inf;
  user_inf.id = GetUserId();
  std::string str_email = incoming.queries["email"];
  std::string str_username = incoming.queries["username"];
  std::string str_passward = incoming.queries["passward"];
  std::strcpy(user_inf.email, str_email.c_str());
  std::strcpy(user_inf.username, str_username.c_str());
  std::strcpy(user_inf.passward, str_passward.c_str());
  user_inf.verified = true;
  user_inf.last_login = v::chrono::utcTime();
  user_inf.is_active = true;
  user_inf.is_staff = true;

  // save a user id at the DB.
  DBUserId(user_inf.id);

  // save a user inf at the DB.
  DBUserInf(user_inf);
}

std::string Login::LocalChangeTime()
{
     //현재 시간 출력
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    std::stringstream strTemp;
    strTemp << t->tm_year+1900 
            << std::setw(2) 
            << std::setfill('0') 
            << t->tm_mon + 1 
            << t->tm_mday 
            << t->tm_hour 
            << t->tm_min 
            << t->tm_sec;

    return strTemp.str();
}

