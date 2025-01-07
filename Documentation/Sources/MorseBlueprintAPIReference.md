# Morse Blueprint API Reference

All the blueprint API is accessibles type "morse" in the blueprint actions.

![alt text](Images/BP_API.png)

## DDS Writer Graph Nodes
This section describes the process of creating a Writer object, which manages the actions of writing data to the Data Distribution Service (DDS). The data type is specified as an input parameter to the function (DataType). The Settings parameter includes the Quality of Service (QoS) settings and the name of the topic on which the data will be published.


![alt text](Images/Writer_BP_Node.png)

To send data using the Writer object, you need to set the data on your data proxy. Once the data is configured, you can invoke the Write function within the Writer to publish the data to the specified topic.

![alt text](Images/Writer_BP_Graph_Nodes.png)

## DDS Reader Graph Nodes
This section describes the process of creating a Reader object, which manages the actions of reading data from the Data Distribution Service (DDS). The data type to be read is specified as an input parameter to the function (DataType). The Settings parameter includes the Quality of Service (QoS) settings and the name of the topic from which we want to receive data.

![alt text](Images/Reader_BP_Node.png)

To retrieve data from DDS, you have two options:

* Bind a Delegate: You can bind a delegate that is triggered when data becomes available on the topic. This approach treats the Reader object as a subscriber, allowing you to react to incoming data in real-time.

* Manual Retrieval: Alternatively, you can manually retrieve the data by calling the Read function on the Reader object. After executing this function, you can access the data within the data proxy.


![alt text](Images/Reader_BP_Graph_Nodes.png)

## DDS Quality Of Service Settings

![alt text](Images/QoS_BP_Settings.png)
