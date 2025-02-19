import sys
import time
import argparse
import math

from cyclonedds.core import Listener, Qos, Policy
from cyclonedds.domain import DomainParticipant
from cyclonedds.topic import Topic
from cyclonedds.pub import Publisher, DataWriter
from cyclonedds.util import duration


from Unreal.Actor._ActorState import ActorState
from Unreal.Math._Geometry import Transform, Vector3, Quaternion

tf_base = Transform(Rotation=Quaternion(0,0,0,0),Scale3D=Vector3(1,1,1),Translation=Vector3(3520.000000,-720.000000,100.000000)) 

def print_transform(transform):
    return f"Transform(Position=({transform.Translation.X:.2f}, {transform.Translation.Y:.2f}, {transform.Translation.Z:.2f}), " \
           f"Rotation=({transform.Rotation.X:.2f}, {transform.Rotation.Y:.2f}, {transform.Rotation.Z:.2f}, {transform.Rotation.X:.2f}), " \
           f"Scale=({transform.Scale3D.X:.2f}, {transform.Scale3D.Y:.2f}, {transform.Scale3D.Z:.2f}))"

def compute_actor_transform(t, base_position=tf_base):
    """
    Compute actor transformation over time.
    
    - Rotation: Uses quaternion representation.
    - Scale: 1 to 3.
    - Position: Varies in X and Y by ±50 cm relative to base position.
    """
    angle_rad = math.radians(t % 360)
    rotation = Quaternion(0, 0, math.sin(angle_rad / 2), math.cos(angle_rad / 2))  # Rotation around Z-axis
    
    scale_value = 1 + 2 * (math.sin(angle_rad) + 1) / 2  # Scale varies from 1 to 3
    
    position = Vector3(
        base_position.Translation.X + math.sin(angle_rad) * 50,  # X varies from base_x ±50 cm
        base_position.Translation.Y + math.cos(angle_rad) * 50,  # Y varies from base_y ±50 cm
        base_position.Translation.Z  # Z remains unchanged
    )
    
    scale = Vector3(scale_value, scale_value, scale_value)
    return Transform(rotation, scale, position)


def main(topic_name, freq):
    """
    Main function to set up the DDS publisher and publish messages on the specified topic.
    """
    qos = Qos(Policy.Durability.TransientLocal)  # QoS settings (default or customized if needed)
    
    # Create a DDS domain participant
    domain_participant = DomainParticipant()
    
    # Create a topic with the given name
    topic = Topic(domain_participant, topic_name, ActorState)
    
    # Create a publisher
    publisher = Publisher(domain_participant)
    writer = DataWriter(domain_participant, topic, qos=qos)
    
    print(f"Publishing on topic: {topic_name} at {freq} Hz")
    
    actor_state=ActorState(Name="MonActeur", Id="123", Transform=tf_base)

    try:
        t = 0
        while True:
            transformation = compute_actor_transform(t)
            print(print_transform(transformation))
            actor_state.Transform = transformation
            writer.write(actor_state)
            t += 1
            time.sleep(1 / freq)
    except KeyboardInterrupt:
        print("\nInterruption detected. Stopping the program.")
        sys.exit(0)

if __name__ == "__main__":
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="DDS Publisher for ActorState topic")
    parser.add_argument("--topic", required=True, help="Specify the topic name")
    parser.add_argument("--freq", type=float, required=True, help="Specify the publishing frequency (Hz)")
    args = parser.parse_args()
    
    # Start the main function with the given topic name and frequency
    main(args.topic, args.freq)