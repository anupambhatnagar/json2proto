Generate protobuf

```
protoc -I=./ --cpp_out=./out ./addressbook.proto
```

Compile on mac

```
g++ -I/opt/homebrew/include -L/opt/homebrew/lib -lprotobuf -std=c++11 write_address.cpp addressbook.pb.cc -o addressbook
```


