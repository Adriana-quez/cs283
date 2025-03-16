1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

        The remote client determines when a command's output is full received based on when it encounters indicators like '\n' or EOF.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

        A network shell protocol should utilize indicators like '\n' to define and detect the beginning and end of a command. If this is not handled correctly, challenges like data corruption or misinterpeted commands could arise. 

3. Describe the general differences between stateful and stateless protocols.

        General differences between stateless and stateful protocols include stateless protocols being faster, having less overhead, but not being fully reliable, while stateful protocols have more robust capabilities but are generally slower with more overhead.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

        Even though UDP is unreliable, it is still great to use for situations where we would need to prioritze speed and efficiency over reliability as well as it preserves message boundaries, unlike TCP.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

        Sockets are provided by the operating system.