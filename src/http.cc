/**
 * Copyright, 2022.
 * This file is 
 * Author: Changhyun Son <xoowoo35@gmail.com>
*/

#include "http.h"



WebInterface::WebInterface()
    : is_exited_(false)
{
    start();
    

    std::cout << "WebInterface Initialization Ended" << std::endl;
}

WebInterface::~WebInterface(){
  TryExit();
  std::cout << "WebInterface Closed" << std::endl;
}

void WebInterface::TryExit(){
  is_exited_ = true;
  stop();
  wait();
}

void WebInterface::thread(){
  std::cout << "WebInterface Thread Starts" << std::endl;
  
  int count = 0;

  fifa_server our_fifa_server;
  // make it listen on port 16850
  our_fifa_server.set_listening_port(PORT);
  // Tell the server to begin accepting connections.
  our_fifa_server.start_async();
  
  while(!is_exited_)
  {
    // create an instance of our web server

    //std::cout << "It is working in the 'our_interface' :" << count++ << std::endl;
    

    dlib::sleep(1000);
  }

  std::cout << "web_interace Thread Ended" << std::endl;
}

const std::string fifa_server::on_request(
    const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing )
{
  std::ostringstream sout;
  outgoing.headers["Content-Type"] = "application/json";
  outgoing.headers["access-control-allow-origin"] = "*";
  outgoing.headers["Access-Control-Allow-Headers"] = "Origin,Content-Type,Accept";
  outgoing.headers["Access-Control-Allow-Methods"] = "GET, POST, OPTIONS";

  /*
  cout << "query test result: " << incoming.queries["restaurant"] << endl;
  cout << "path = "         << incoming.path << endl;
  cout << "request_type = " << incoming.request_type << endl;
  cout << "content_type = " << incoming.content_type << endl;
  cout << "protocol = "     << incoming.protocol << endl;
  cout << "foreign_ip = "   << incoming.foreign_ip << endl;
  cout << "foreign_port = " << incoming.foreign_port << endl;
  cout << "local_ip = "     << incoming.local_ip << endl;
  cout << "local_port = "   << incoming.local_port << endl;
  cout << "body = \""       << incoming.body << "\"" << endl;
  */

  sout << url_login(incoming, "/login");
  sout << url_signup(incoming, "/signup");

  return sout.str();
}

fifa_server::fifa_server(){

}

string fifa_server::url_login(
      const dlib::incoming_things& incoming, 
      string message) {
  string path_str = incoming.path;

  std::ostringstream sout;
  if(path_str.find(message) != std::string::npos)
  {
    Login login;
    sout << "{ \"success\" : " << login.LoginParse(incoming) << " }" ;
  }   

  return sout.str();
}

string fifa_server::url_signup(
      const dlib::incoming_things& incoming, 
      string message) {
  
  string path_str = incoming.path;
  LOG(INFO) << path_str.find(message);
  std::ostringstream sout;
  if(path_str.find(message) != std::string::npos)
  {
    // 저장
    Login login; 
    login.SignUpParse(incoming);
    sout << "{ \"success\" : \"true\"  }" ;
  }   

  return sout.str();
}

string fifa_server::ReadFileIntoString(const string& path)
{
    ifstream input_file(path);
    if(!input_file.is_open()) {
        cerr << "Could not open the file - '"
        << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string(
      (std::istreambuf_iterator<char>(input_file)), 
      std::istreambuf_iterator<char>());
}

string fifa_server::localchangetime()
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

