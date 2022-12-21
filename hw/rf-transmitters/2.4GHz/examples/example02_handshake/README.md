# Two-way transmission

If the slave is required to send data back to the master it would seem necessary for the two devices to swap roles. Among other things that will mean that the "master" will need an address as well as the slave. The question of timing also needs to be considered - for example, how long should the master continue listening for the reply from the slave? And, if the slave is trying to write rather than listen it may miss a transmission from the master.

# Two-way transmission using the ackPayload concept

The complications of swapping roles can be completely avoided by using the ackPayload concept. The idea is that the slave puts data in the ackPayload buffer BEFORE it receives a message from the master and then the data in the ackPayload buffer is sent automatically as part of the normal acknowledgment process without your code needing to make the devices swap roles.

The ackPayload concept can only be used when the amount of data transferring from slave to master is 32 bytes or less.

It also means that the data sent from the slave is always a step behind the data received by the slave. For example the ackPayoad cannot take account of the data received in the message for which it is the acknowledgment.

# ackPayload example

In this example the slave will send a pair of numbers back to the master.
