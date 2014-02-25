
#ifndef IPC_DATAREADER_H
#define IPC_DATAREADER_H


// this calss is supposed to be used to stream data, which then can
// be read with 'IPC_DataReader'
class IPC_DataReader {
	
public:
	IPC_DataReader();
	virtual ~IPC_DataReader();

private:
	Stream stream;
	
};

#endif // #ifndef IPC_DATAREADER_H
