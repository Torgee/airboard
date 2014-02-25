

#ifndef DATASTREAMER_H
#define DATASTREAMER_H


// this calss is supposed to be used to stream data, which then can
// be read with 'IPC_DataReader'
// this will most probably be replaced by a more specific
// 'SharedMemory_DataStreamer', 'MemoryMappedFile_DataStreamer' or
// something along those lines
class IPC_DataStreamer {
	
public:
	IPC_DataStreamer();
	virtual ~IPC_DataStreamer();

private:
	Stream stream;
	
};

#endif // #ifndef DATASTREAMER_H
