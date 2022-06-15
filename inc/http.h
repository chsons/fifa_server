/**
 * Copyright, 2022, Polaris3d.co. All rights reserved.
 * This file is 
 * Author: Changhyun Son <xoowoo3@polarsi3d.co>
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



#define PORT 33515


using namespace std;
using namespace dlib;

class WebInterface : public dlib::threaded_object
{
  
public:
WebInterface();
~WebInterface();
void TryExit();

private:


void thread();
bool is_exited_;
  
};


class web_server : public dlib::server_http
{
const std::string on_request(
    const dlib::incoming_things& incoming, 
    dlib::outgoing_things& outgoing);
public:
  web_server();
  string ReadFileIntoString(const string& path);
  string process_request(
      const dlib::incoming_things& incoming, string message);
  string process_response_menu(
      const dlib::incoming_things& incoming, string message);
  string process_response_return(
      const dlib::incoming_things& incoming, string message);
  string localchangetime();
};
