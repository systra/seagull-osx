
     binary-body-not-interp protocol

     version 1.2.2


Support of binary protocol defined by a message with a binary header
and a not interpreted body part.

---------------------------------------

0. Protocol package content

1. Description 

2. Dictionary 

3. Configuration

4. Scenario 

5. Usage (sample)

6. Getting support

---------------------------------------

0. Protocol package content

   The installation of the module seagull-core 
   on your platform creates the following files:
   
   /usr/local/bin/
           seagull
           computestat.ksh
           plotstat.ksh
           startoctave_plot.ksh
           startoctave_stat.ksh
           csvextract
           csvsplit
           [library-files].so

   /usr/local/bin directory contains the binaries of Seagull. 
   Make sure that this directory is in your user path by typing:

   $>  type seagull
       seagull is /usr/local/bin/seagull
      
   If Seagull can't be found, type:
   $>  export PATH=$PATH:/usr/local/bin

   After installation of the module seagull-binary-body-not-interp-protocol,
   the Seagull directory contains an binary-body-not-interp directory:
     /opt/seagull/binary-body-not-interp         
   that contains the directories config, doc, run and scenario with the 
   following content:
   /opt/seagull/binary-body-not-interp/
       +--- config
       | bin-not-inter-dico.xml              xml dictionnary file
       | conf.client.xml                     sample of client configuration file
       | conf.server.xml                     sample of server configuration file
       +--- doc
       | README-binary-body-not-interp.txt   this file
       +--- run
       | start_client_1.ksh                  launch script examples              
       | start_client_2.ksh
       | start_server_1.ksh
       | start_server_2.ksh
       +--- scenario
       | client_1.xml                        scenario examples
       | client_2.xml
       | server_1.xml
       | server_2.xml


1. Description
   
   This protocol (binary body not interpreted) has the same functionalities
   as binary protocol (like diameter...) but the body message part is not
   interpreted. 

   Body not interpreted means that you can put what you want in this part.

   Example :  here you are an example of a body not interpreted :
   <parameter name="body" 
                 value=",000000000001,0000000002,0,0000000000,0000000000,Call lasted 0:03 and cost 15.00 GBP. You have 6655.90 GBP remaining,">
   </parameter>


2. Dictionary 

   The description of dictionary is done in bin-body-not-interp-dico.xml file. 

   The dictionary file is specified using the -dico parameter on the command 
   line.

   This dictionary contains the same parts as binary protocol: 
    <types>, <header>, <body> and <dictionary>. 
    We detail the parts which interest us. 

     - The header part:  we have to add a section <start-length></start-length> 
       to know from which the length of Data is computed.
       Then, the field "LengthOfData" is used to store the length of the message
       starting from the field "CommandId" in the following example.

       Example:

       <header name="command" length="LengthOfData" type="CommandId">
        <fielddef name="LengthOfData"  size="4" unit="octet"></fielddef>
        <fielddef name="Padding"       size="2" unit="octet"></fielddef>
        <start-length></start-length>
        <fielddef name="CommandId"     size="2" unit="octet"></fielddef>
        <fielddef name="TypeIndicator" size="2" unit="octet"></fielddef>
       </header>

       Now, if you receive a message with 15 octets the lengthOfData is 9
          15 - 4 - 2 = 9 octets.  


     - The body part contains only the name of the parameter (in our case it 
       is "parameter"):
       the content of this parameter is not interpreted.
     
       <body>
          <header name="parameter"></header>
       </body>

     - The dictionary part contains the definitions of the parameters and 
       the definitions of the messages like in the binary protocol.    

       a) "parameter" section (specific body part definition) : 

        This section is used to interpret some parts of the body (if needed),
        and generally to extract from the body the session id, ...
   
        Example:

        <parameter>
         <define name="SDPTransactionId-1"  type="String" size="1"  unit="octet" position="1">
         </define>
         <define name="SDPTransactionId-12" type="String" size="12" unit="octet" position="1">
         </define>
        </parameter>
       
       Explanation:

         - the parameter "SDPTransactionId-1" is of type STRING its size is 
           1 byte and it is at position 1 in the body

         - the parameter "SDPTransactionId-12" is of type STRING its size is 
           12 bytes and it is at position 1 in the body


       WARNING : Be careful, in the body the count for the positions start from 
                 zero.

     b) "message" section :

       In this section you define the session-id, out-of-session-id and the 
       differents messages.

       Reminder : the session-id is useful to find or retrieve a call, 
                  if this session-id is not exist in the message received 
                  seagull use out-of-session-id field. 

       Only in binary body not interpreted protocol, you can define many 
       differente out-of-session-id 

       Example : here you are an example of session-id and out-of-session_id:

           <command session-id="SDPTransactionId-12" 
                    out-of-session-id="SDPTransactionId-1"                                          
                    out-of-session-id="CommandId">
 
       In this section you define the different messages, 
       Example:      
        <define name="SessionConnectRequest">
           <setfield name="Padding"       value="0"></setfield>
           <setfield name="CommandId"     value="0x1012"></setfield>
           <setfield name="TypeIndicator" value="0"></setfield>
           <not-present name="SDPTransactionId-1"></not-present>
           <not-present name="SDPTransactionId-12"></not-present>
        </define>


       Explanation of not present tag:

           This message contains neither "SDPTransactionId-1" parameter nor
           "SDPTransactionId-12" parameter then you can identify your call with 
           the parameter of header out-of-session-id="CommandId".

       Now, for this message 

        <define name="NewCall">
           <setfield name="Padding"       value="0"></setfield>
           <setfield name="CommandId"     value="0x1013"></setfield>
           <setfield name="TypeIndicator" value="0"></setfield>
           <not-present name="SDPTransactionId-1"></not-present>
        </define>

       you can identify your call with "SDPTransactionId-12" parameter 

       Note: In the second message you can not use out-of-session-id="CommandId"
             because it is unique and its value is define in the message 
             defintion.

3. Configuration

   The configuration file contains the same informations that you can find in 
   binary protocol.
     
   The generic configuration (including network and other parameters) is 
   different for the client and the server.
    
   The client uses conf.client.xml and the server uses conf.server.xml. 

   The configuration file is specified using the -conf <conf_file_name> 
   parameter on the command line.

   To have more information about configurations files 
   (cf. /opt/seagull/binary-body-not-interp/config/conf.client.xml 
    and /opt/seagull/binary-body-not-interp/config/conf.server.xml) 


4. Scenario 

   The scenario file is specified using the -scen <scen_file_name> parameter on 
   the command line.

   The scenario file (including counters defintion, init scenario, 
   traffic scenario and default scenarios) is different for the client and 
   the server. 

   Example of different scenarii parts:

   <send channel="channel-1">
    <action>
      <inc-counter name="session-counter"></inc-counter>
      <set-value name="SDPTransactionId-12"
                 format="$(session-counter)"
                 fill-pattern="0" fill-size="12">
      </set-value>
    </action>
    <command name="NewCall">
      <parameter name="body" value=",000000000001,0000000001,2,1,1,1,44166174323,1,1,0722919262,1,1,0722919263,26-01-200617:29:52,+04,0000013879,">
      </parameter>
    </command>
       ...
   </send>
  
  <receive channel="channel-1">
       ...
    <comand name="NewCallResponse">
    </command>
    <action>
       <store name="SESSION-ID" entity="body" begin="1" end="13"></store>
    </action>
  </receive>
  ...

  ...
  <receive channel="channel-1">
    ...
    <command name="NewCallResponse">
    </command>
    <action>
      <store name="SESSION-ID" entity="SDPTransactionId-12"></store> 
    </action>
  </receive>

  ...
  <send channel="channel-1">
    <action>
      <restore name="SESSION-ID"  entity="SDPTransactionId-12"></restore> 
    </action>
    <command name="CallerReleased">
      <parameter name="body" value=",000000000001,0000000002,0722919263,0722919262,26-01-200617:29:52,+04,3,0,1,">
      </parameter>
    </command>
  </send>
  ...

  
  <send channel="channel-1">
    <action>
       <restore name="SESSION-ID" entity="body" begin="1" end="13"></restore> 
    </action>
    <command name="CallerReleased">
      <parameter name="body" value=",000000000001,0000000002,0722919263,0722919262,26-01-200617:29:52,+04,3,0,1,">
      </parameter>
    </command>
  </send>
  ...
 

   a) Explanation for <set-value> section : 
     
      
     Since this version <set-value> action supports a new attributes
        
      fill-size="12"   : indicate the size of your parameter
      fill-pattern="0" : fill the buffer with 0 to attempt 12 bytes. 


     In our case, you have 
   SDPTransactionId-12 = "00 00 00 00 00 00 00 00 00 00 00 31" for the  1st call
   SDPTransactionId-12 = "00 00 00 00 00 00 00 00 00 00 00 32" for the  2nd call
      ...
   SDPTransactionId-12 = "00 00 00 00 00 00 00 00 00 00 31 30" for the 10th call
      etc.

   Note 1 : you can added a fix part in your format of counter for example
                   format="123$(session-counter)"
   SDPTransactionId-12 = "00 00 00 00 00 00 00 00 31 32 33 31" for the  1st call
      ...
   SDPTransactionId-12 = "00 00 00 00 00 00 00 31 32 33 31 30" for the 10th call

   Note 2 : Be careful, if your counter attempt the max of the fill-size 
            (for example 3 to ease the example) 

          SDPTransactionId-12 = "00 00 30" for the   1st call 
            ...
          SDPTransactionId-12 = "39 39 39" for the 999th call

      Now, the next call SDPTransactionId-12 have the follow value

          SDPTransactionId-12 = "31 30 30 30" for the 1000th call 
          SDPTransactionId-12 = "31 30 30 31" for the 1001th call     

   b) Explanation for parameter in the send message : 

      Be careful, the name of parameter "body" is implicite in the dictionary 
      but you can use it in the scenario to indiquate the contain of body.

         <parameter name="body" value=",000000000001,0000000001,2,1,1,1,44166174323,1,1,0722919262,1,1,0722919263,26-01-200617:29:52,+04,0000013879,">
         </parameter>

      the value of the body is not interpreted, 
      but you can use the store/restore to extract/inject data in this body.

   c) Explanation for store action in the receive message : 

      You have two methods to extract the session-id from a message  
        <store name="SESSION-ID" entity="body" begin="1" end="13"></store>
          or 
        <store name="SESSION-ID" entity="SDPTransactionId-12"></store> 
      
      Note : you can extract an other data if you now the position of your 
             parameter.

      
   d) Explanation for restore action in the send message : 

      You have two methods to inject the session-id in your message  

      <restore name="SESSION-ID"  entity="SDPTransactionId-12"></restore> 
        or 
      <restore name="SESSION-ID" entity="body" begin="1" end="13"></restore> 

      Note : you can inject an other data from an external file if you now 
             the position of your parameter.


   To have more information about sceanrio files.        
(cf. /opt/seagull/binary-body-not-interp/scenario/client_<1/2>.xml 
 and /opt/seagull/binary-body-not-interp/scenario/server_<1/2>.xml) 

   Note : you can use the different actions that can be used in <send> or 
          <receive> commands these actions are descrinbing in seagull-refdoc.


5. Usage (sample)
   
   Open two terminal sessions. Terminal 2 will be the server and Terminal 1 
   the client. 
   Examples are located in the "run" directory. 
   So the first thing you need to do is to go in this directory 
   (in both terminal windows):
     $> cd run
   In Terminal 2 window type:
     $> ./start_server_1.ksh
   In Terminal 1 window type:
     $> ./start_client_1.ksh


   if you put the logging level on A (using -llevel A on commande line),
   you can take a look at the log file  client.date.log and server.date.log.

   Example : Here you are an example of one call: 

   Client Side : 

2006-02-02.18:13:25.922|M|Send [[SessionConnectRequest
                       |M|[LengthOfData] = [ 0]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4114]
                       |M|[TypeIndicator] = [ 0]
                       |M| [body
                       |M| ] = [
                       |M| [2c 53 41 43 2c 32 2c 39 2c ] <=> [,SAC,2,9,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:25.923|B|Buffer sent size [19]
                       |B|00 00 00 0d 00 00 10 12 00 00 2c 53 41 43 2c 32 
                       |B|2c 39 2c 
2006-02-02.18:13:25.924|B|Buffer received size [15]
                       |B|00 00 00 09 00 00 10 12 00 01 2c 32 2c 39 2c 
2006-02-02.18:13:25.924|M|Received [[SessionConnectRequest
                       |M|[LengthOfData] = [ 9]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4114]
                       |M|[TypeIndicator] = [ 1]
                       |M| [body
                       |M| ] = [
                       |M| [2c 32 2c 39 2c ] <=> [,2,9,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:26.915|M|Send [[NewCall
                       |M|[LengthOfData] = [ 0]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4115]
                       |M|[TypeIndicator] = [ 0]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 31 2c 32 2c 31 2c 31 2c 31 ] <=> [00000001,2,1,1,1]
                       |M| [2c 34 34 31 36 36 31 37 34 33 32 33 2c 31 2c 31 ] <=> [,44166174323,1,1]
                       |M| [2c 30 37 32 32 39 31 39 32 36 32 2c 31 2c 31 2c ] <=> [,0722919262,1,1,]
                       |M| [30 37 32 32 39 31 39 32 36 33 2c 32 36 2d 30 31 ] <=> [0722919263,26-01]
                       |M| [2d 32 30 30 36 31 37 3a 32 39 3a 35 32 2c 2b 30 ] <=> [-200617:29:52,+0]
                       |M| [34 2c 30 30 30 30 30 31 33 38 37 39 2c ] <=> [4,0000013879,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:26.916|B|Buffer sent size [119]
                       |B|00 00 00 71 00 00 10 13 00 00 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 31 2c 32 2c 31 2c 31 2c 31 2c 34 34 31 36 36 
                       |B|31 37 34 33 32 33 2c 31 2c 31 2c 30 37 32 32 39 
                       |B|31 39 32 36 32 2c 31 2c 31 2c 30 37 32 32 39 31 
                       |B|39 32 36 33 2c 32 36 2d 30 31 2d 32 30 30 36 31 
                       |B|37 3a 32 39 3a 35 32 2c 2b 30 34 2c 30 30 30 30 
                       |B|30 31 33 38 37 39 2c 
2006-02-02.18:13:26.917|B|Buffer received size [52]
                       |B|00 00 00 2e 00 00 10 13 00 01 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 31 2c 33 39 30 30 2c 30 2c 31 2c 31 2c 30 2c 
                       |B|2c 2c 2c 2c 
2006-02-02.18:13:26.917|M|Received [[NewCall
                       |M|[LengthOfData] = [ 46]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4115]
                       |M|[TypeIndicator] = [ 1]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 31 2c 33 39 30 30 2c 30 2c ] <=> [00000001,3900,0,]
                       |M| [31 2c 31 2c 30 2c 2c 2c 2c 2c ] <=> [1,1,0,,,,,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:29.915|M|Send [[CallerReleased
                       |M|[LengthOfData] = [ 0]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4112]
                       |M|[TypeIndicator] = [ 0]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 32 2c 30 37 32 32 39 31 39 ] <=> [00000002,0722919]
                       |M| [32 36 33 2c 30 37 32 32 39 31 39 32 36 32 2c 32 ] <=> [263,0722919262,2]
                       |M| [36 2d 30 31 2d 32 30 30 36 31 37 3a 32 39 3a 35 ] <=> [6-01-200617:29:5]
                       |M| [32 2c 2b 30 34 2c 33 2c 30 2c 31 2c ] <=> [2,+04,3,0,1,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:29.916|B|Buffer sent size [86]
                       |B|00 00 00 50 00 00 10 10 00 00 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 32 2c 30 37 32 32 39 31 39 32 36 33 2c 30 37 
                       |B|32 32 39 31 39 32 36 32 2c 32 36 2d 30 31 2d 32 
                       |B|30 30 36 31 37 3a 32 39 3a 35 32 2c 2b 30 34 2c 
                       |B|33 2c 30 2c 31 2c 
2006-02-02.18:13:29.917|B|Buffer received size [127]
                       |B|00 00 00 79 00 00 10 10 00 01 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 32 2c 30 2c 30 30 30 30 30 30 30 30 30 30 2c 
                       |B|30 30 30 30 30 30 30 30 30 30 2c 43 61 6c 6c 20 
                       |B|6c 61 73 74 65 64 20 30 3a 30 33 20 61 6e 64 20 
                       |B|63 6f 73 74 20 31 35 2e 30 30 20 47 42 50 2e 20 
                       |B|59 6f 75 20 68 61 76 65 20 36 36 35 35 2e 39 30 
                       |B|20 47 42 50 20 72 65 6d 61 69 6e 69 6e 67 2c 
2006-02-02.18:13:29.917|M|Received [[CallerReleased
                       |M|[LengthOfData] = [ 121]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4112]
                       |M|[TypeIndicator] = [ 1]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 32 2c 30 2c 30 30 30 30 30 ] <=> [00000002,0,00000]
                       |M| [30 30 30 30 30 2c 30 30 30 30 30 30 30 30 30 30 ] <=> [00000,0000000000]
                       |M| [2c 43 61 6c 6c 20 6c 61 73 74 65 64 20 30 3a 30 ] <=> [,Call lasted 0:0]
                       |M| [33 20 61 6e 64 20 63 6f 73 74 20 31 35 2e 30 30 ] <=> [3 and cost 15.00]
                       |M| [20 47 42 50 2e 20 59 6f 75 20 68 61 76 65 20 36 ] <=> [ GBP. You have 6]
                       |M| [36 35 35 2e 39 30 20 47 42 50 20 72 65 6d 61 69 ] <=> [655.90 GBP remai]
                       |M| [6e 69 6e 67 2c ] <=> [ning,]
                       |M| ]
                       |M|]]

   Server Side :

2006-02-02.18:13:25.923|B|Buffer received size [19]
                       |B|00 00 00 0d 00 00 10 12 00 00 2c 53 41 43 2c 32 
                       |B|2c 39 2c 
2006-02-02.18:13:25.923|M|Received [[SessionConnectRequest
                       |M|[LengthOfData] = [ 13]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4114]
                       |M|[TypeIndicator] = [ 0]
                       |M| [body
                       |M| ] = [
                       |M| [2c 53 41 43 2c 32 2c 39 2c ] <=> [,SAC,2,9,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:25.923|M|Send [[SessionConnectResponse
                       |M|[LengthOfData] = [ 0]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4114]
                       |M|[TypeIndicator] = [ 1]
                       |M| [body
                       |M| ] = [
                       |M| [2c 32 2c 39 2c ] <=> [,2,9,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:25.924|B|Buffer sent size [15]
                       |B|00 00 00 09 00 00 10 12 00 01 2c 32 2c 39 2c 
2006-02-02.18:13:26.916|B|Buffer received size [119]
                       |B|00 00 00 71 00 00 10 13 00 00 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 31 2c 32 2c 31 2c 31 2c 31 2c 34 34 31 36 36 
                       |B|31 37 34 33 32 33 2c 31 2c 31 2c 30 37 32 32 39 
                       |B|31 39 32 36 32 2c 31 2c 31 2c 30 37 32 32 39 31 
                       |B|39 32 36 33 2c 32 36 2d 30 31 2d 32 30 30 36 31 
                       |B|37 3a 32 39 3a 35 32 2c 2b 30 34 2c 30 30 30 30 
                       |B|30 31 33 38 37 39 2c 
2006-02-02.18:13:26.916|M|Received [[NewCall
                       |M|[LengthOfData] = [ 113]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4115]
                       |M|[TypeIndicator] = [ 0]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 31 2c 32 2c 31 2c 31 2c 31 ] <=> [00000001,2,1,1,1]
                       |M| [2c 34 34 31 36 36 31 37 34 33 32 33 2c 31 2c 31 ] <=> [,44166174323,1,1]
                       |M| [2c 30 37 32 32 39 31 39 32 36 32 2c 31 2c 31 2c ] <=> [,0722919262,1,1,]
                       |M| [30 37 32 32 39 31 39 32 36 33 2c 32 36 2d 30 31 ] <=> [0722919263,26-01]
                       |M| [2d 32 30 30 36 31 37 3a 32 39 3a 35 32 2c 2b 30 ] <=> [-200617:29:52,+0]
                       |M| [34 2c 30 30 30 30 30 31 33 38 37 39 2c ] <=> [4,0000013879,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:26.917|M|Send [[NewCallResponse
                       |M|[LengthOfData] = [ 0]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4115]
                       |M|[TypeIndicator] = [ 1]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 31 2c 33 39 30 30 2c 30 2c ] <=> [00000001,3900,0,]
                       |M| [31 2c 31 2c 30 2c 2c 2c 2c 2c ] <=> [1,1,0,,,,,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:26.917|B|Buffer sent size [52]
                       |B|00 00 00 2e 00 00 10 13 00 01 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 31 2c 33 39 30 30 2c 30 2c 31 2c 31 2c 30 2c 
                       |B|2c 2c 2c 2c 
2006-02-02.18:13:29.916|B|Buffer received size [86]
                       |B|00 00 00 50 00 00 10 10 00 00 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 32 2c 30 37 32 32 39 31 39 32 36 33 2c 30 37 
                       |B|32 32 39 31 39 32 36 32 2c 32 36 2d 30 31 2d 32 
                       |B|30 30 36 31 37 3a 32 39 3a 35 32 2c 2b 30 34 2c 
                       |B|33 2c 30 2c 31 2c 
2006-02-02.18:13:29.916|M|Received [[CallerReleased
                       |M|[LengthOfData] = [ 80]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4112]
                       |M|[TypeIndicator] = [ 0]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 32 2c 30 37 32 32 39 31 39 ] <=> [00000002,0722919]
                       |M| [32 36 33 2c 30 37 32 32 39 31 39 32 36 32 2c 32 ] <=> [263,0722919262,2]
                       |M| [36 2d 30 31 2d 32 30 30 36 31 37 3a 32 39 3a 35 ] <=> [6-01-200617:29:5]
                       |M| [32 2c 2b 30 34 2c 33 2c 30 2c 31 2c ] <=> [2,+04,3,0,1,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:29.917|M|Send [[BalanceUpdate
                       |M|[LengthOfData] = [ 0]
                       |M|[Padding] = [ 0]
                       |M|[CommandId] = [ 4112]
                       |M|[TypeIndicator] = [ 1]
                       |M| [body
                       |M| ] = [
                       |M| [2c 00 00 00 00 00 00 00 00 00 00 00 31 2c 30 30 ] <=> [,...........1,00]
                       |M| [30 30 30 30 30 30 30 32 2c 30 2c 30 30 30 30 30 ] <=> [00000002,0,00000]
                       |M| [30 30 30 30 30 2c 30 30 30 30 30 30 30 30 30 30 ] <=> [00000,0000000000]
                       |M| [2c 43 61 6c 6c 20 6c 61 73 74 65 64 20 30 3a 30 ] <=> [,Call lasted 0:0]
                       |M| [33 20 61 6e 64 20 63 6f 73 74 20 31 35 2e 30 30 ] <=> [3 and cost 15.00]
                       |M| [20 47 42 50 2e 20 59 6f 75 20 68 61 76 65 20 36 ] <=> [ GBP. You have 6]
                       |M| [36 35 35 2e 39 30 20 47 42 50 20 72 65 6d 61 69 ] <=> [655.90 GBP remai]
                       |M| [6e 69 6e 67 2c ] <=> [ning,]
                       |M| ]
                       |M|]]
2006-02-02.18:13:29.917|B|Buffer sent size [127]
                       |B|00 00 00 79 00 00 10 10 00 01 2c 00 00 00 00 00 
                       |B|00 00 00 00 00 00 31 2c 30 30 30 30 30 30 30 30 
                       |B|30 32 2c 30 2c 30 30 30 30 30 30 30 30 30 30 2c 
                       |B|30 30 30 30 30 30 30 30 30 30 2c 43 61 6c 6c 20 
                       |B|6c 61 73 74 65 64 20 30 3a 30 33 20 61 6e 64 20 
                       |B|63 6f 73 74 20 31 35 2e 30 30 20 47 42 50 2e 20 
                       |B|59 6f 75 20 68 61 76 65 20 36 36 35 35 2e 39 30 
                       |B|20 47 42 50 20 72 65 6d 61 69 6e 69 6e 67 2c 


    Note: un-printable characters are printed like points.


6. Getting support

   - For support on Seagull, please contact Olivier Jacques: 
        olivier.jacques@hp.com (mailto:olivier.jacques@hp.com).

   - For HP personal only:
     a) Go to the Seagull homepage 
        (http://qai.telecom.hp.com/test_inf/tools/homepage/seagull.aspx) 
         for latest support information.
         
     b) Contact Seagull internal support: tool_support@ocbu.grenoble.hp.com 
         (mailto:tool_support@ocbu.grenoble.hp.com).
         
     c) If you need training or other kind of support for Seagull, 
        contact Olivier JACQUES (http://peoplefinder.portal.hp.com/peoplefinder/detail.asp?target='uid=olivier.jacques@hp.com,+ou=People,+o=hp.com').
