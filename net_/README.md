*This project has been created as part of the 42 curriculum by Raulsanc.*

# NetPractice

## Description

**NetPractice** is a networking project whose goal is to understand and apply the basics of **TCP/IP addressing**. Through a series of practical exercises, the project introduces core networking concepts such as **IP addresses**, **subnet masks**, **default gateways**, and the role of **routers** and **switches** in a network.

Each level presents a **non-functioning simulated network diagram**. The goal is to modify the editable fields (IP addresses, subnet masks, gateways, routing tables) until every host in the diagram can correctly communicate with its target(s), according to the objectives displayed for that level. The project is composed of **10 levels**, each one increasing in complexity, covering scenarios that go from a single subnet to multi-router topologies requiring proper routing table configuration.

This project does not involve writing code — it focuses on developing a solid understanding of how addressing and routing work in a network, which is a fundamental skill for any developer or system administrator.

## Instructions

### Running the training interface

1. Download and extract the NetPractice files into a folder of your choice.
2. From that folder, run the provided shell script:
   ```bash
   ./run.sh
   ```
   This will start a local web server and automatically open the training interface in your default web browser.
3. If `run.sh` does not work for any reason, you can start the server manually:
   ```bash
   python3 -m http.server 49242
   ```
   Then open your browser and navigate to:
   ```
   http://localhost:49242
   ```
   (or whichever port you chose).

### Using the interface

- On the welcome screen, enter your **intranet login** (`Raulsanc`) in the **Training** tab to generate your personal configuration, or use the **Evaluation** tab to generate a random configuration suitable for evaluations.
- For each level, a network diagram is displayed with one or more **objectives** at the top of the screen.
- Edit the **unshaded fields** (IP addresses, subnet masks, gateways, routes) so that the network works as intended.
- Use **[Check again]** to verify whether your current configuration solves the level.
- Check the **logs** at the bottom of the page for hints on what is wrong (e.g. missing gateway, invalid IP, unreachable destination, etc.).
- Once a level is solved, click **[Next level]** to move on to the next exercise.

### Exporting configurations

- Before moving on to the next level, click **[Get my config]** to download the configuration file for that level.
- Repeat this process for **all 10 levels**.

### Submission requirements

- The 10 exported configuration files (one per level) must be placed at the **root** of this repository.
- This `README.md` file must also be located at the **root** of the repository.
- No subfolders are used — everything is submitted directly at the repository root.
- Login used for this submission: **Raulsanc**.

## Resources

Documentation and material used to understand and complete this project:

- General documentation on **TCP/IP addressing**, including how IPv4 addresses are structured and assigned.
- References on **subnet masks** and subnetting (CIDR notation, how a mask determines the network and host portions of an address).
- Material on **default gateways** and how a host uses them to reach destinations outside its own subnet.
- Documentation on **routers and switches**, their role in forwarding traffic between networks, and how routing tables are used to determine the next hop.
- Introductory material on the **OSI model**, in particular the Network layer (Layer 3), to better understand how addressing and routing fit into the overall communication stack.
- Course material and notes from the 42 curriculum studied prior to and during this project.

### AI usage

AI (Claude) was used during this project strictly as a **support and learning tool**, not to solve the exercises directly:

- To clarify theoretical networking concepts (subnetting, gateway behavior, routing tables) when explanations in the documentation were unclear.
- To help translate and organize the project instructions (this `README.md`) into a clear structure.
- To review and proofread the wording of this README.

No AI tool was used to solve the NetPractice levels themselves — all network configurations were completed manually, tested through the training interface's **[Check again]** feature, and validated by understanding the logs provided by the tool.
