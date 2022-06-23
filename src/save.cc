/**
 * Copyright, 2022.
 * This file is 
 * Author: Changhyun Son <xoowoo35@gmail.com>
*/
#include "save.h"

int Login::GetUserId()
{
  std::vector<int> ret_user_id;
  if(db_client.GetListData<int>(
        key_user_id, ret_user_id) != db_client.kSuccess)
  {
    LOG(ERROR) << "GetListData: It can't find the key about USER_INF";
    return 0;
  }
  else return ret_user_id.size();
}
void Login::DBUserId(int user_id)
{
  if(db_client.PushDataOnList<int>
        (key_user_id, user_id) != db_client.kSuccess ) 
  {
    LOG(ERROR) << "PushDataOnList: It can't find the key about USER_ID";
  }
}
void Login::DBUserInf(UserInf user_inf)
{
  if(db_client.PushDataOnList<UserInf>(
        key_user_inf, user_inf) != db_client.kSuccess ) 
  {
    LOG(ERROR) << "PushDataOnList: It can't find the key about USER_INF";
  }
}
bool Login::CheckingID(std::vector<UserInf> vec_user_inf, string user_email, string user_passward)
{ 
  for(int i = 0; i < vec_user_inf.size(); i++)
  {
    std::string get_email(vec_user_inf[i].email); 
    if(get_email.compare(user_email) == 0)
    {
      std::string get_passward(vec_user_inf[i].passward);
      return CheckingPW(get_passward, user_passward);
    } 
  }
  return false;
}
bool Login::CheckingPW(string get_passward, string user_passward)
{
  if(get_passward.compare(user_passward) == 0) return true;
  else return false;
}
int Login::CheckingPassward(string queries)
{
  if(queries.size() < 8 || queries.size() > 20 ) return 
}
bool Login::CheckingOverlapEmail(string queries)
{
  std::vector<UserInf> vec_user_inf;
  if(db_client.GetListData<UserInf>(
        key_user_inf, vec_user_inf) != db_client.kSuccess)
  {
    LOG(ERROR) << "GetListData: It can't find the key about USER_INF";
  }

  for (int i = 0; i < vec_user_inf.size(); i++)
  {
    if(queries.compare(vec_user_inf[i].email) == 0) return false;
  }
  return true;

}
RpnsStyle1 Login::SignUpParse(const dlib::incoming_things& incoming)
{
  RpnsStyle1 sign_respose; 
  // checking overlap Email and Username
  if( CheckingOverlapEmail(incoming.queries["email"]) != true ) sign_respose.result = 1;
  if( CheckingPassward(incoming.queries["passward"] != true) )

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
bool Login::LoginParse(const dlib::incoming_things& incoming)
{
  std::vector<UserInf> vec_user_inf;
  std::string get_key = regularDbItemKeys::fifa::USER_INF;
  if(db_client.GetListData<UserInf>(
        get_key, vec_user_inf) != db_client.kSuccess)
  {
    LOG(ERROR) << "GetListData: It cannot find the key about USER_INF";
  }

  std::string str_email = incoming.queries["email"];
  std::string str_passward = incoming.queries["passward"];

  return CheckingID(vec_user_inf, str_email, str_passward);
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

