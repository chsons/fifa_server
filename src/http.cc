/**
 * Copyright, 2022, Polaris3d.co. All rights reserved.
 * This file is 
 * Author: Changhyun Son <xoowoo3@polarsi3d.co>
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

  web_server our_web_server;
  // make it listen on port 33505
  our_web_server.set_listening_port(PORT);
  // Tell the server to begin accepting connections.
  our_web_server.start_async();
  
  while(!is_exited_)
  {
    // create an instance of our web server

    //std::cout << "It is working in the 'our_interface' :" << count++ << std::endl;
    

    dlib::sleep(1000);
  }

  std::cout << "web_interace Thread Ended" << std::endl;
}

const std::string web_server::on_request(
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


  sout << process_request(incoming, "/menu_list");

  return sout.str();
}

web_server::web_server(){

}

string web_server::process_request(
      const dlib::incoming_things& incoming, 
      string message) {
  LOG(INFO) << "web page --> server: requset";
  string path_str = incoming.path;

  std::ostringstream sout;
  if(path_str.find(message) != std::string::npos)
  {
    std::string filename("./menu_inf_data.json");

    sout << ReadFileIntoString(filename);

  }   

  return sout.str();
}

string web_server::ReadFileIntoString(const string& path)
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

string web_server::localchangetime()
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

