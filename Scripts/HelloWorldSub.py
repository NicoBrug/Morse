import sys
import time
import argparse

from cyclonedds.core import Listener, Qos
from cyclonedds.domain import DomainParticipant
from cyclonedds.topic import Topic
from cyclonedds.sub import Subscriber, DataReader
from cyclonedds.util import duration

from Unreal.Exemple._HelloWorld import HelloWorld


class HelloWorldListener(Listener):
    """
    Custom listener for handling DDS events such as liveliness change and data reception.
    """
    def on_liveliness_changed(self, reader, status):
        print(">> Liveliness event detected")
    
    def on_data_available(self, reader):
        """Called when new data is available on the topic."""
        for sample in reader.take_iter(timeout=duration(seconds=0.5)):
            # Uncomment the following line to display specific fields
            print(f"Received message: {sample.HelloStr}, {sample.HelloFloat}")

def main(topic_name):
    """
    Main function to set up the DDS subscriber and listen for messages on the specified topic.
    """
    qos = Qos()  # QoS settings (default or customized if needed)
    
    # Create a DDS domain participant
    domain_participant = DomainParticipant()
    
    # Create a topic with the given name
    topic = Topic(domain_participant, topic_name, HelloWorld)  # Replace 'HelloWorld' with your message type
    
    # Create a subscriber
    subscriber = Subscriber(domain_participant)
    
    # Create a data reader with the custom listener
    hello_listener = HelloWorldListener()
    reader = DataReader(domain_participant, topic, qos=qos, listener=hello_listener)
    
    print(f"Listening on topic: {topic_name}")
    
    try:
        while True:
            pass  # Keep the script running to listen for messages
    except KeyboardInterrupt:
        print("\nInterruption detected. Stopping the program.")
        sys.exit(0)


if __name__ == "__main__":
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="DDS Subscriber for HelloWorld topic")
    parser.add_argument("--topic", required=True, help="Specify the topic name")
    args = parser.parse_args()
    
    # Start the main function with the given topic name
    main(args.topic)