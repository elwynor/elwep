<pre>
    ______                _                    ____   __  __       
   / ____/___ ___  ____  (_)_______     ____  / __/  / /_/ /_  ___ 
  / __/ / __ `__ \/ __ \/ / ___/ _ \   / __ \/ /_   / __/ __ \/ _ \
 / /___/ / / / / / /_/ / / /  /  __/  / /_/ / __/  / /_/ / / /  __/
/_____/_/ /_/ /_/ .___/_/_/   \___/   \____/_/     \__/_/ /_/\___/ 
               /_/                                                 
              ____                              __      
             / __ \___  ____ __________ _____  / /______
            / /_/ / _ \/ __ `/ ___/ __ `/ __ \/ __/ ___/
           / ____/  __/ /_/ (__  ) /_/ / / / / /_(__  ) 
          /_/    \___/\__,_/____/\__,_/_/ /_/\__/____/  

                        version 2.03
           Copyright (c) 2024 Elwynor Technologies
</pre>

## WHAT IS EMPIRE OF THE PEASANTS?

 Empire of the Peasants is a game of war and economics.  Each player
 must build their empire from the ground up.   Players clash on the
 battlefield to fight over their empires.  Players must also keep a close
 watch on their taxation rate and their grain and coin production.
 If grain production falls short of that required by the serfs and soldiers,
 they will surely starve.  A player caught severely neglecting their serfs
 and soldiers will undoubtedly be beheaded!
 
## GAMEPLAY

 There are several added features to this version. First off, there is a
 new "MESSAGE CENTER". The message center allows you to send private "page"
 type messages to other users (internal to EOP). The message center also
 allows you to send single line "courier" messages to other players. These
 single line courier messages are also sent internally by EOP to players
 to notify them of situations (like battle results, etc). The main goal
 of the message centers "Leave a message" option is to provide users with
 notification of important events.
 
 Secondly, there are four new "users" internal to the pub now. You can use
 the LOOK command for information on these characters - along with the
 normal players. The number of characters that show up each time you
 use the LOOK command is random (possibility of 4 at one time). You can use
 normal action commands with these "internal" users to generate responces
 from them. Profanity does not go over well with these "internal" users.
 
 Next, the flow of EOP has changed for the better. When you select the
 "C"ontinue option, you will answer "Y"es or "N"o if you wish to
 buy/sell grain/land. Selecting "N"o will send you on to the
 distribution of grain to serfs and soldiers. The EOP market place prices
 are now level 4 configurable.

## COMMANDS

### A. Main Menu
<pre>
       Empire Master Selections
       ========================
   ====                        ====
   =      [C]ontinue Quest        =
   =      [N]ews of the land      =
   =      [T]ax rate adjustment   =
   =      [Y]our Status           =
   =      [O]ther Players         =
   =      [P]ub (Talk it up!)     =
   =      [+] Transfer Menu       =
   =      [Q]uit (Wimp out)       =
   =      [?] Redisplays Menu     =
   ================================

 Empire (C,N,T,Y,O,P,+,Q or ? for menu)
</pre>
 
### B. Market Menu:
<pre>
 +++++++++++++++++++++++
 + Empire Market INC   +
 +++++++++++++++++++++++++++++++++++++++
 + Investment   Coins+   Can afford    +
 +++++++++++++++++++++++++++++++++++++++
    Soldiers        4+      <value>
    Markets       400+      <value>
    Mills         700+      <value>
    Foundries    1600+      <value>
    Shipyards    1800+      <value>
    Palaces      5000+      <value>
    Nobles       6400+      <value>
 +++++++++++++++++++++++++++++++++++++++
  Enter HELP PURCHASE for purchase info
 +++++++++++++++++++++++++++++++++++++++
</pre>
#### 1. Commands available at the market:
<pre>
    buy or b
    sell or s
  
    Command form:  buy 20 soldiers
    sell 20 soldiers
</pre>

#### 2. Basic rules about purchases

<pre>
    Each player may only own 20 soldiers per noble
    Each player gets 1 free noble with each palace purchased
    You must keep a ratio of one market to every three mills
</pre>
 
### End of a turn

 Each turn, players are informed of what resources have produced for
 the current turn. Players are also informed of any money gained
 from taxes.
<pre>
 A example is as follows:
 
 Markets....  30000  coins
 Mills......  20000 bags of grain
 Foundries..  1000 coins
 Shipyards..  1000 coins
 
 Your loyal serfs paid taxes at 10 percent!
</pre> 

### Battle commands

 Empire of the Peasants supports several commands while in
 battle. They are as follows:
<pre>
 ATTACK  - Full scale attack (Hand to Hand soldier combat)
 CONQUER - Attempt to destroy some of opponents palace
 RETREAT - Run from battle (May take casualties)
 
 Battle commands can be abbreviated for ease of use.
</pre> 

### Information about the PUB:
 
 The PUB is a place inside Empire of the Peasants (EOP) where
 users can talk to one another. While inside the PUB, users can
 talk around one of 65,000 available "tables". Some tables are
 reserved for LIVE users only, and some are for SYSOPS only. Tables
 1-10 are for NON-LIVE use. Depending on how the SYSOP has configured
 the EOP game, NON-LIVE users may or may not be able to enter the PUB,
 speak inside the PUB, use action commands, whisper, changes tables, etc.
 
 The PUB supports an unlimited number of action commands to be used. To
 use an action command, simply enter the action. For a full list of
 actions available, enter "/a" or "list".
 
 For a full list of commands available inside the PUB, enter '?' while
 in the PUB.

<pre>
 Several SYSOP commands are available inside the PUB:

 The PUB supports entrance/exit messages for each player. To modify the
 entrance/exit message for a particular user, use the following command:
  EDIT <userid>

  -----------------------------------------------------------------
  A menu is now provided for modifying entrance/exit messages. You
  can exit the menu by entering "X".
  -----------------------------------------------------------------

 The PUB supports action words that can be modified by the sysop(s)
 as desired.  The add or update an action command, use the following:

  CHANGE <action word>

  An example includes:

  CHANGE LAUGH

  EOP would display the following:

  The action word entered does not exist in the
  pub action word database. Adding word to database. You
  can enter 'X' to abort this process.


  -----------------------------------------------------------------
  A menu is now provided for modifying action word information. You
  can exit the menu by entering "X".
  -----------------------------------------------------------------

 To remove an action command, use the following command:

  DELETE <action>
</pre>

## Ranking system of Empire of the Peasants

 The following is a chart indicating the player requirements in
 order to move up in the ranks of EOP:

<pre> 
 ---------------------------------------------------------------
 | Rank    |  Land       | Nobles | Markets | Mills    | Turns |
 ---------------------------------------------------------------
 | Peasant |   *******   |   ***  |  ****   |    ****  |  **** |
 | Master  |     3,500   |    15  |    15   |      20  |   5   |
 | Duke    |    15,000   |    60  |    60   |      75  |   8   |
 | Lord    |   100,000   |  1500  |  2200   |    3500  |   10  |
 | King    | 2,000,000   |   50k  |   50k   |     30k  |   20  |
 | Emperor | 7,500,000   |  100k  |  100k   |     75k  |   35  |
 ---------------------------------------------------------------
 
 o  NOBLES  indicates how many nobles the player has aquired.  NOBLES
            can be directly bought for 25,000 coins each or you can
            buy 10% palace and receive a NOBLE "on the house".
 
 o  TURNS   indicates how many turns the player has successfully
           completed since becomming a new player
</pre>

## Online HELP
<pre>
 Empire of the Peasants has help on FIFTEEN different topics of interest. To
 obtain help, enter the command HELP followed by the topic. Typing HELP
 alone will display a list of topics. The following topics are
 available:
 
 GENERAL       -    General information about EOP
 RANKS         -    Information about rank requirements
 STRATEGY      -    Strategic information
 TRANSFERS     -    Information on EOP transfer options
 NEWS          -    Information about EOP system news
 TAXES         -    Tax information
 OTHERS        -    Information you need to know about others
 PUB           -    Information about how to use the PUB
 EXITING       -    Exiting EOP Information
 BATTLE        -    Information about BATTLE commands
 PURCHASE      -    Information about the EOP Market Menu
 GROWTH        -    Information on how to make your empire grow
 PROTECTION    -    Defense Information
 TURNS         -    Information about how turns work
 PALACE        -    Information on what palace means to you!
</pre>

## Online SYSOP menu
<pre>
 <<< Empire of the Peasants SYSOP Sub-menu >>>
 
 1 ==> ACTTOG is (%s)  (Non-live users allowed to use action commands?)
 2 ==> TLKTOG is (%s)  (Non-live users allowed to talk in pub?)
 3 ==> ATTTOG is (%s)  (Non-live users allowed to attack others?)
 4 ==> ENTTOG is (%s)  (Non-live users custom entrance msg displayed?)
 5 ==> EXITOG is (%s)  (Non-live users custom exit msg displayed?)
 6 ==> RNKTOG is (%s)  (Non-live users can change ranks?)
 7 ==> WSPTOG is (%s)  (Non-live users allowed to whisper?)
 8 ==> CHATOG is (%s)  (Non-live users allowed to change tables?)
 9 ==> PUBTOG is (%s)  (Non-live users allowed in pub?)
 0 ==> NLVEMP is (%s)  (Non-live users allowed to play empire?)
 X ==> Exit to game
</pre> 
 All of the above items are "Level 4" configuration options and can be
 toggled while ONLINE. To access the Sysop menu, enter "MENU" at the
 MAIN Empire of the Peasants menu. All items toggled above are changed
 only for the duration of the current BBS session. If the BBS is rebooted
 for any reason, the above options return to DEFAULT settings.
<pre>
 Other SYSOP functions

  VAL - Validates a user into Empire of the Peasants that is
  currently waiting to be validated. When a user waiting to
  be validated "(*)" appears next to a userid in the "O"ther listing.

  GRANT - Grants a user (3) extra turns of play. A user is only
  permitted to play a configurable number of times per hour.

  OVERLOOK - Displays the stats for a user which is online at
  the moment.

  BEHEAD - Kills and removes a player from Empire of
  the Peasants. The player is completely removed from the
  game records.
</pre>

## INSTALLATION AND CONFIGURATION
 
 Simply unzip the game archive to your BBS server directory, add Empire 
 of the Peasants to your menu, configure the MSG file to your liking, and 
 start the BBS!  It's that easy! 
  
 Finally, there are many new configuration options which have been added. Such
 options as support for Game-ops, configuring market prices, etc. have
 been added to the game. See the editor to modify any of these new options.

 Here are the default values for the standard configuration options:
<pre>
 TUREMK {Empire Number of turns per hour: 3} N 1 32000
 TAXEMK {Empire Default tax rate: 5} N 1 50
 PALEMK {Empire Default palace: 1} N 1 10
 COUEMK {Empire Default starting turn: 1} N 1 10
 MAREMK {Empire Default number of markets: 60} N 0 32000
 MILEMK {Empire Default number of mills: 180} N 0 32000
 FOUEMK {Empire Default number of foundries: 20} N 0 32000
 SHIEMK {Empire Default number of shipyards: 20} N 0 32000
 SEREMK {Empire Default number of serfs: 1697} N 1000 10000
 NOBEMK {Empire Default number of nobles: 2} N 0 32000
 SOLEMK {Empire Default number of soldiers: 20} N 0 32000
 GRAEMK {Empire Default bags of grain: 32000} N 5000 32000
 MONEMK {Empire Default of coins: 32000} N 0 32000
 LANEMK {Empire Default acres of land: 2500} N 1000 32000
 ACTTOG {Empire allow non-live to use action commands? YES} B
 PUBTOG {Empire allow non-live users into pub? YES} B
 TLKTOG {Empire allow non-live to talk in pub? YES} B
 ATTTOG {Empire allow non-live to attack others? YES} B
 ENTTOG {Empire allow non-live to own entrance message? YES} B
 EXITOG {Empire allow non-live to own exit message? YES} B
 RNKTOG {Empire allow non-live to change rank? YES} B
 WSPTOG {Empire allow non-live users to whisper? YES} B
 CHATOG {Empire allow non-live users to change tables? YES} B
 VALTOG {Empire automatic validation of new players? YES} B
 ACCTOG {Empire new players accepted into game? YES} B
</pre> 

## GAME HISTORY
 
 Empire of the Peasants was developed by MagiComm.  The game was based upon
 several other POLitical/ECONomic simulations popular on single-user BBSes as
 well as on Galacticomm systems.  
 
 The game was sold to Logicom when MagiComm went out of business in the early
 1990s, and hasn't been available since. Don Arnel transferred the game to
 Elwynor Technologies in June 2007.
 
 Elwynor Technologies ported the game to Worldgroup 3.2 in June 2012.
 
 The game was ported to Major BBS V10 in May 2023.
 
## LICENSE

 This project is licensed under the AGPL v3. Additional terms apply to 
 contributions and derivative projects. Please see the LICENSE file for 
 more details.

## CONTRIBUTING

 We welcome contributions from the community. By contributing, you agree to the
 terms outlined in the CONTRIBUTING file.

## CREATING A FORK

 If you create an entirely new project based on this work, it must be licensed 
 under the AGPL v3, assign all right, title, and interest, including all 
 copyrights, in and to your fork to Rick Hadsall and Elwynor Technologies, and 
 you must include the additional terms from the LICENSE file in your project's 
 LICENSE file.

## COMPILATION

 This is a Worldgroup 3.2 / Major BBS v10 module. It's compiled using Borland
 C/C++ 5.0 for Worldgroup 3.2. If you have a working Worldgroup 3.2 development
 kit, a simple "make -f ELWEP" should do it! For Major BBS v10, import this
 project folder in the isv/ subtree of Visual Studio 2022, right click the
 project name and choose build! When ready to build for "release", ensure you
 are building for release.

## PACKING UP

 The DIST folder includes all of the items that should be packaged up in a 
 ELWEP.ZIP. When unzipped in a Worldgroup 3.2 or Major BBS V10 installation 
 folder, it "installs" the module.
