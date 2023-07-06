#include <iostream>
#include <fstream>
#include <string>
#include "perfetto_trace.pb.h"

using namespace std;
using TracePacket = perfetto::protos::TracePacket;
using TrackDescriptor = perfetto::protos::TrackDescriptor;
using ProcessDescriptor = perfetto::protos::ProcessDescriptor;
using ThreadDescriptor = perfetto::protos::ThreadDescriptor;
using TrackEvent = perfetto::protos::TrackEvent;

int main()
{
  // write the data read from the json in the protobuf format
  //fstream output("out.trace", ios::out | ios::app | ios::binary);
  string data;

  perfetto::protos::Trace* t = new perfetto::protos::Trace();

  // first packet
  ProcessDescriptor* pd = new ProcessDescriptor();
  string s1 = "a special process";
  pd->set_pid(1234);
  pd->set_allocated_process_name(&s1);

  TrackDescriptor* trd1 = new TrackDescriptor();
//  trd1->set_uuid(8948);
  trd1->set_allocated_process(pd);

  TracePacket* tp1 = t->add_packet();
  tp1->set_allocated_track_descriptor(trd1);
  tp1->SerializeToString(&data);

  // second packet
  ThreadDescriptor* tid1 = new ThreadDescriptor();
  string s2 = "a special thread";
  tid1->set_pid(1234);
  tid1->set_tid(5678);
//  tid1->set_allocated_thread_name(&s2);

  TrackDescriptor* trd2 = new TrackDescriptor();
  trd2->set_uuid(4908);
//  trd2->set_parent_uuid(8948);
  trd2->set_allocated_thread(tid1);

  TracePacket* tp2 = t->add_packet();
  tp2->set_allocated_track_descriptor(trd2);
  tp2->SerializeToString(&data);

  // third packet
  TrackEvent* e1 = new TrackEvent();
  string name = "a special event";
  e1->set_type(perfetto::protos::TrackEvent_Type_TYPE_SLICE_BEGIN);
  e1->set_allocated_name(&name);
  e1->set_track_uuid(4908);

  TracePacket* tp3 = t->add_packet();
  tp3->set_allocated_track_event(e1);
  tp3->set_timestamp(200);
  tp3->set_trusted_packet_sequence_id(145);
  tp3->SerializeToString(&data);

  // fourth packet
  TrackEvent* e2 = new TrackEvent();
  string name2 = "a special child event";
  e2->set_type(perfetto::protos::TrackEvent_Type_TYPE_SLICE_BEGIN);
  e2->set_allocated_name(&name2);
  e2->set_track_uuid(4908);

  TracePacket* tp4 = t->add_packet();
  tp4->set_allocated_track_event(e2);
  tp4->set_timestamp(250);
  tp4->set_trusted_packet_sequence_id(145);
  tp4->SerializeToString(&data);

  // instant event
  TrackEvent* c1 = new TrackEvent();
  c1->set_type(perfetto::protos::TrackEvent_Type_TYPE_INSTANT);
  c1->set_track_uuid(4908);

  TracePacket* tp7 = t->add_packet();
  tp7->set_timestamp(285);
  tp7->set_trusted_packet_sequence_id(145);
  tp7->set_allocated_track_event(c1);
  tp7->SerializeToString(&data);

  // fifth packet
  TrackEvent* e3 = new TrackEvent();
  e3->set_type(perfetto::protos::TrackEvent_Type_TYPE_SLICE_END);
  e3->set_track_uuid(4908);

  TracePacket* tp5 = t->add_packet();
  tp5->set_allocated_track_event(e3);
  tp5->set_timestamp(290);
  tp5->set_trusted_packet_sequence_id(145);
  tp5->SerializeToString(&data);

  // sixth packet
  TrackEvent* e4 = new TrackEvent();
  e4->set_type(perfetto::protos::TrackEvent_Type_TYPE_SLICE_END);
  e4->set_track_uuid(4908);

  TracePacket* tp6 = t->add_packet();
  tp6->set_allocated_track_event(e4);
  tp6->set_timestamp(300);
  tp6->set_trusted_packet_sequence_id(145);
  tp6->SerializeToString(&data);

  cout<<t->DebugString() <<endl;
  fstream output("out.trace", ios::out | ios::trunc | ios::binary);
  t->SerializeToOstream(&output);
  // unwrap to check
  /*
  TracePacket tp;
  tp.ParseFromString(data);
  TrackDescriptor td = tp.track_descriptor();
  ProcessDescriptor pd1 = td.process();
  assert(td.uuid() == 1308);
  assert(pd1.pid() == 1234);
  assert(pd1.process_name() == "a special process");
  */
}
