# Touch Sequencer
## Classes/Architecture
* ofApp - the encapsulating class
* Playhead - lines that move across the screen, triggering osc when they cross nodes. created by swiping finger. 
* PlayheadSeed - a (not drawn) data structure to store direction and velocity information during finger swipes. When released, they create Playheads that move in the average speed and direction of the finger swipe. 
* Node - visible points that trigger osc when they are crossed by playheads.
* NodeSeed - a (not drawn_ data structure to store finger position when trackpad is being used to create Nodees. When release, they create nodes at last known position of the finger.
* TouchManager - a wrapper class I made on top of a trackpad addon with methods to retreive new, existing, and removed touches from the trackpad. 
* OscSender- Sends OSC via UDP

## Datastructures
* Collections of Playhead, PlayheadSeed, Node, NodeSeed   
* std::map<Playhead*, std::map<Node*, float> > to store the last known projection coefficient of each node onto each playhead


## Building  
* Open the XCode project, build release the release version, and open it.  
* The sequencer outputs OSC, so sound was rendered in Max for Live. Made this decision to allow control over other arbitrary timbres in the future. Also, it allowed me to focus my energy on making the playhead crossing over a node animation as satisfying as possible.  

## Usage, changing modes
* 'n': node mode. tap to create nodes
* 'p': playhead mode. swipe to create playheads
* 'c': chill mode. touches are ignored

## Future work  
* bpm synced metrnonomes
* better looking playheads
* nodes decay over time
* playheads decay over time
* pitch shift with arrow keys
