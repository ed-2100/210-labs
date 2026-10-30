// Import necessary headers

// Use namespace std

// `tick` function declaration

// `main` function

// Process executible path into input directory

// Load input file into communal job queue (100 items)

// Define state map

// Iterate across the compute nodes using the modulo operator and queue
// jobs into Pending queues until the communal job queue is empty

// Announce starting state

// Display current compute cluster status

// Announce time stepping

// Tick loop (25 times)

// For each compute node, run `tick()` on its 3-list array

// Display current compute cluster status

// End tick loop

// Announce time stepping finished

// Display current compute cluster status

// End `main` function

// Begin `tick` function

// If Active not empty, then

// De-queue one item from Active and queue it into Completed

// End if

// While Pending not empty and length of active less than 5,

// De-queue one item from Pending and queue it into Active

// End while

// End `tick` function