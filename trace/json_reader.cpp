#include <iostream>
#include <fstream>
#include <string>
#include <json.hpp>
#include "perfetto_trace.pb.h"

using namespace std;
using json = nlohmann::json;
using bjson = nlohmann::basic_json<>;
using Trace = perfetto::protos::Trace;
using TracePacket = perfetto::protos::TracePacket;
using TrackDescriptor = perfetto::protos::TrackDescriptor;
using ProcessDescriptor = perfetto::protos::ProcessDescriptor;
using ThreadDescriptor = perfetto::protos::ThreadDescriptor;
using TrackEvent = perfetto::protos::TrackEvent;

int main()
{
  // Read json file
  std::ifstream f("/Users/anupamb/pb_example/proto_trace/data/single_event.json");
  json data = json::parse(f);
  vector<bjson> add = data.at("traceEvents");

  for(auto it = add.begin(); it != add.end(); ++it){
    bjson t = *it;
    cout <<"name: " << t["name"] << endl;
    cout <<"cat: " << t["cat"] << endl;
    cout <<"phase: " << t["ph"] << endl;
    cout <<"start_time: " << t["ts"] << endl;
    cout <<"duration: " << t["dur"] << endl;
    cout <<"pid: " << t["pid"] << endl;
    cout <<"tid: " << t["tid"] << endl;
  }

  // write the data read from the json in the protobuf format
  fstream output("out.trace", ios::out | ios::app | ios::binary);

  // first packet
  ProcessDescriptor* pd = new ProcessDescriptor();
  string s1 = "a special process";
  pd->set_pid(1234);
  pd->set_allocated_process_name(&s1);

  TrackDescriptor* trd1 = new TrackDescriptor();
  trd1->set_uuid(1308);
  trd1->set_allocated_process(pd);

  TracePacket* tp1 = new TracePacket();
  tp1->set_allocated_track_descriptor(trd1);
  if (! tp1->SerializeToOstream(&output)) {
    cerr << "Failed to write tp1." << endl;
    return -1;
  }

  // second packet
  ThreadDescriptor* tid1 = new ThreadDescriptor();
  string s2 = "a special thread";
  tid1->set_pid(1234);
  tid1->set_tid(5678);
  tid1->set_allocated_thread_name(&s2);

  TrackDescriptor* trd2 = new TrackDescriptor();
  trd2->set_uuid(4908);
  trd2->set_parent_uuid(1308);
  trd2->set_allocated_thread(tid1);

  TracePacket* tp2 = new TracePacket();
  tp2->set_allocated_track_descriptor(trd2);

  if (! tp2->SerializeToOstream(&output)) {
    cerr << "Failed to write tp2." << endl;
    return -1;
  }

  // third packet
  TrackEvent* e1 = new TrackEvent();
  string name = "a special event";
  e1->set_type(perfetto::protos::TrackEvent_Type_TYPE_SLICE_BEGIN);
  e1->set_allocated_name(&name);
  e1->set_track_uuid(4908);

  TracePacket* tp3 = new TracePacket();
  tp3->set_allocated_track_event(e1);
  tp3->set_timestamp(200);
  tp3->set_trusted_packet_sequence_id(145);

  if (! tp3->SerializeToOstream(&output)) {
    cerr << "Failed to write tp3." << endl;
    return -1;
  }

  // fourth packet
  TrackEvent* e2 = new TrackEvent();
  e2->set_type(perfetto::protos::TrackEvent_Type_TYPE_SLICE_END);
  e2->set_track_uuid(4908);

  TracePacket* tp4 = new TracePacket();
  tp4->set_allocated_track_event(e2);
  tp4->set_timestamp(250);
  tp4->set_trusted_packet_sequence_id(145);
    if (! tp4->SerializeToOstream(&output)) {
      cerr << "Failed to write tp4." << endl;
      return -1;
    }

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
