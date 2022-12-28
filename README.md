# Introduction

This year, the MATE ROV Competition is highlighting the [United Nations Decade of Ocean Science for Sustainable Development](https://en.unesco.org/ocean-decade) and aligning its mission tasks with one or more of the [17 UN Sustainable Development Goals](https://www.un.org/sustainabledevelopment/sustainable-development-goals/). This 2023 MATE ROV Competition also continues to inspire ESG principles in order to do “good for good” for our ocean, planet, and global community.


# Mission

Design and implement a float capable of completing a vertical profile (i.e., travelling from the surface to the bottom and back to the surface) and communicating data to the mission station. 

## Buoyancy engine

The float's descent and ascent profiles are controlled by a buoyancy engine. The mechanism moves fluid from inside the float to outside the float, displacing seawater and changing the density of the float.

## Data transmission

The float must also be capable of transmitting data to a receiving device (i.e.,
a receiver) located at the surface mission station. The data is both the team number and the current "UTC" time.


# Point System

**UN Sustainable Development Goal: Climate Action**

| Points            | Description                                                   |
| ----------------- | ------------------------------------------------------------- |
| 5                 | design and construct an operational vertical profiling float  |
| 10                | communicates with the mission station prior to descending     |
|                   |                                                               |
| 10                | demonstrate buoyancy engine to descend/ascend                 |
| 10                | relay data to mission station after reaching surface          |
|                   |                                                               |
| 10                | buoyancy engine to descend/ascend                             |
| 15                | communicate to mission station when surfaced                  |


# Key Deadlines

Below is an updated summary of key dates and deadlines for the 2023 MATE ROV competition season. Note that regional competitions will have their own set of key dates and deadlines. For companies attending regionals, contact your [regional coordinator or visit your regional contest’s website](https://www.materovcompetition.org/regionals) for more information.

* December 1, 2022: Registration opens (note that registration for the World Championship and
individual regional competitions will open as locations and dates are secured).
* April 26, 2023: Last day to register for the fluid power quiz.
* May 15, 2023: Last day to submit laser specifications, hydraulic fluid information, and pressure
release specifications. Companies with regional competitions earlier than May 15 should plan to
submit specifications early to allow at least 1 week for approval.
* May 15, 2023: [RANGER class video demonstration](https://materovcompetition.org/rangerspecs) submission deadline.
* May 24, 2023:
    * Technical documentation
    * Company spec sheet
    * SIDs (including electrical, fluid, Non-ROV Device)
    * Non-ROV device design document
    * Company safety review
    * Job site safety analysis (optional)
    * Corporate responsibility documentation (optional)


# Installation

1. Install **[git](https://git-scm.com/)**
2. open a new instance to `git bash`
3. enter the follow lines:
    ```
    $ cd ~/Documents/projects && projects
    $ git clone https://github.com/Tektronica/profiling-float
    ```
