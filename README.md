
# vHPC

This project is meant to be a GUI visualization of local HPC environments based off virtual machines. 

The goal is to be able to create and manage nodes and manage networking. Similar to how you would manage a physical HPC cluster.
On top of that, having workspaces of different clusters, node templates and being able to share setups with others.
It's an amalgamation of Vagrant, GNS3 and OpenStack.

This is also a learning project for me to learn C and raylib. With that said, very much a work in progress.

## To-Do

### GUI

#### Canvas
- [x] Scrollable canvas
- [x] Dotted grid canvas
- [x] Adding items to the canvas
- [x] Move items across the canvas
- [ ] Graduate from shapes to icons
- [ ] "cables" between nodes

#### UI
- [ ] Modal
- [ ] Sidebar

### API
- [ ] Get node status
- [ ] Create and manage nodes
- [ ] Syncing node state
- [ ] Storing node state
- [ ] Managing network


## Bugs

- Wayland, cursor coordinates not aligning with cursor when mouse down and not in full screen mode
- Wayland (again), scaling issues....
