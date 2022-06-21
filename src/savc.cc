/**
 * Copyright, 2022.
 * This file is 
 * Author: Changhyun Son <xoowoo35@gmail.com>
*/
#include "save.h"

int Login::GetUserId();
{
  std::vector<int> ret_user_id;
  std::string get_key = regularDbItemKeys::fifa::USER_ID;
  if(db_client.GetListData<int>(
        get_key, ret_user_id) != db_client.kSuccess)
  {
    LOG(ERREOR) << "GetListData: It can't find the key about USER_INF";
  }

  return ret_user_id.size();
}
void Login::DBUserId(int user_id)
{
  std::string get_key = regularDbItemKeys::fifa::USER_ID;
  if(db_client.PushDataOnList<int>
        (get_key, user_id) != db_client.KSuccess ) 
  {
    LOG(ERREOR) << "PushDataOnList: It can't find the key about USER_ID";
  }
}
void Login::DBUserInf(UserInf user_inf)
{
  std::string get_key = regularDbItemKeys::fifa::USER_INF;
  if(db_client.PushDataOnList<UserInf>
        (get_key, user_inf) != db_client.KSuccess ) 
  {
    LOG(ERREOR) << "PushDataOnList: It can't find the key about USER_INF";
  }
}
void Login::SignUpParse(const dlib::incoming_things& incoming)
{
  UserInf user_inf;
  user_inf.id = GetUserId();
  user_inf.email = incoming.queries["email"];
  user_inf.username = incoming.queries["username"];
  user_inf.passward = incoming.queries["passward"];
  user_inf.verified = true;
  user_inf.last_login = v::chrono::utcTime();
  user_inf.is_active = true;
  user_inf.is_staff = true;

  // save a user id at the DB.
  DBUserId(user_inf.id);

  // save a user inf at the DB.
  DBUserInf(user_inf);
}

string Login::LocalChangeTime()
{
     //현재 시간 출력
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    stringstream strTemp;
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

