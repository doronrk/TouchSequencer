# Touch Sequencer
## Function
* Add mode
    * touch and release adds a node that stays after release
* Remove mode
    * touch and release removes the node neraest the release
* Sustain mode
    * touch and hold adds nodes that are removed when the touch is released
    * if the touch event starts on an existing node, the node gets moved
* Playhead create mode
    * supports multiple playheads at different speeds and directions
    * would be interesting to see what would happen if each playhead played back the notes at different octaves
    * maybe each playhead could also be a pitch shift, x,y coordinate of node carries no pitch information
    * swipe your finger across the pad to create linear playheads that move in the 
    speed and direction of the swipe.
    * how to delete them!?

* double tap on a node quantizes its position
* sends osc to live


Done:
    - Swipe to create playhead
    - Click to create node
    - playhead passing node makes print statement
    - find a way to delete nodes/playheads
    - Create nodes using trackpad
    - playhead passing node sends OSC midi
    - make the nodes look cool
        - have a cool animation when a playhead passes a node
        - Make the nodes look like they're breathing


Features:
    - special key to create/remove a "metronome playhead" that moves horizontally across the space according to a bpm

    - make the playheads look cool
    - scale the speed of all the playheads simultaneously 
    - have the playheads "budge" the nodes
    - playheads can decellerate, die when they get to speed 0
    - Add data to playheads
