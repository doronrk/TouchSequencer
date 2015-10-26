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

\sum_{i=1}^{n} \sum_{j=1}^{n} z_{i} K_{(i j)} z_{j} \\
