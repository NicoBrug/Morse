
## What's DDS?
The Data Distribution Service (DDS) is a middleware protocol designed for real-time data exchange in distributed systems. It facilitates the sharing of information between multiple applications across various platforms, promoting interoperability and scalability.

### Key Concepts of DDS

#### Data Centricity

DDS emphasizes a data-centric approach, meaning that the focus is on the data itself rather than on the individual applications or nodes that produce or consume that data. This allows for a more flexible and efficient way to manage data distribution in real-time systems, as data is defined and managed centrally, enabling seamless access and sharing among various participants in a distributed environment.

#### Global Data Space

DDS operates within a global data space, where all published data is available to any interested subscriber. This concept eliminates the need for point-to-point connections, allowing for dynamic and scalable interactions among distributed systems. Each piece of data is associated with a specific topic, and subscribers can access data from anywhere in the network, ensuring that all components have a consistent view of the shared information.

#### Quality of Service (QoS)

Quality of Service (QoS) policies in DDS provide fine-tuned control over how data is delivered and managed. These policies define parameters such as reliability, durability, and latency, allowing developers to tailor data exchange to meet specific application requirements. For example, a simulation requiring real-time updates might prioritize low latency and high reliability, while another application might need to ensure data persistence even when subscribers are offline.

#### Dynamic Discovery

DDS features a dynamic discovery mechanism that automatically identifies publishers and subscribers in the network. This capability simplifies the integration of new components, as they can join and interact with the system without manual configuration. As new participants publish or subscribe to topics, DDS handles the necessary connections, making it easier to scale applications and adapt to changing network conditions.
