Steam Database Parser V2
=====

Handles parsing the Steam API and storing it in a MySQL database.

### How To Install, Build, and Run

```shell
# install (TODO)
apt-get install g++

# build
make # Build production-ready Parser
# or
make test # Build Parser that uses fake data to test functionality.

# run
./build/run # Interface for setting up the database
./build/queue_worker & # Run worker asynchronously
./build/queue_worker & # Run worker asynchronously
./build/expired_worker & # Run worker asynchronously
```

This example involves two queue workers and one expired worker but the number of each are arbitrary. Any number of workers can be operating on the same database without fear of interrupting each other.

Additionally, the workers do not have to run on the same machine the Database is on. If configured properly, any machine that can run this code (it should run on any Linux machine) can run unlimited workers.

The workers will automatically stop using a key when it hits 90,000 (extra tolerance recommended here, just in case our count doesn't line up with Steam's) uses in the last 24 hours. Once the 24 hours is up, it will use the key again.

### TODO
- Finish Database Setup (API Keys table with counter and date since counter started).
- Ability to add API Keys via build/run
- Finish port of queue worker from PHP to C++.
- Expired worker: determine freshness according to tolerance.
- Ability to start up an arbitrary number of workers in parser.
