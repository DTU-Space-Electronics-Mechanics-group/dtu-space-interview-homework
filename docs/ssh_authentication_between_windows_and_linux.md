# Setting Up SSH Key Pair Authentication Between Windows and Linux for VSCode

## Step 1: Generate SSH Key Pair on Windows

1. **Open PowerShell or Command Prompt on Windows:**
   - Press `Win + R`, type `powershell` or `cmd`, and press `Enter`.

2. **Generate the SSH Key Pair:**
   ```sh
   ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
   ```
   - You will be prompted to specify a file location to save the key. Press `Enter` to accept the default location (`C:\Users\YourUsername\.ssh\id_rsa`).
   - Optionally, you can set a passphrase for an additional layer of security.

## Step 2: Copy Public Key to the Linux Machine

1. **Copy the Public Key:**
   - Use `ssh-copy-id` to copy the public key to your Linux machine. Replace `username` and `remote_host` with your actual username and the IP address or hostname of your Linux machine:
     ```sh
     ssh-copy-id username@remote_host
     ```
   - If `ssh-copy-id` is not available, you can manually copy the key:
     - Display the contents of your public key:
       ```sh
       cat ~/.ssh/id_rsa.pub
       ```
     - Copy the output.
     - On your Linux machine, open the `authorized_keys` file:
       ```sh
       nano ~/.ssh/authorized_keys
       ```
     - Paste the copied key into the file and save it.

## Step 3: Configure SSH on the Linux Machine

1. **Ensure SSH Service is Running:**
   ```sh
   sudo systemctl start ssh
   sudo systemctl enable ssh
   ```

2. **Set Permissions (if manually copied):**
   ```sh
   chmod 600 ~/.ssh/authorized_keys
   ```

## Step 4: Test SSH Connection

1. **Connect from Windows to Linux:**
   ```sh
   ssh username@remote_host
   ```
   - You should be able to connect without being prompted for a password.

## Step 5: Configure VSCode for Remote SSH

1. **Install Remote Development Extension Pack:**
   - Open VSCode.
   - Go to the Extensions view by pressing `Ctrl+Shift+X`.
   - Search for `Remote Development` and install the extension pack by Microsoft.

2. **Add SSH Host in VSCode:**
   - Open the Command Palette by pressing `Ctrl+Shift+P`.
   - Type and select `Remote-SSH: Add New SSH Host...`.
   - Enter the SSH connection string `username@remote_host` and select the default SSH configuration file (`~/.ssh/config`).

3. **Configure SSH Options:**
   - VSCode will open the SSH configuration file. You can add additional configuration options here. For example:
     ```sh
     Host remote_host_alias
       HostName remote_host
       User username
       IdentityFile ~/.ssh/id_rsa
     ```
   - Save the file.

4. **Connect to the SSH Host:**
   - Open the Command Palette again (`Ctrl+Shift+P`).
   - Type and select `Remote-SSH: Connect to Host...`.
   - Choose the host you just configured (`remote_host_alias`).

## Step 6: Open Folder in Remote Machine

1. **Open a Remote Folder:**
   - Once connected to the remote host, you can open a folder on the remote machine by selecting `File -> Open Folder` and navigating to the desired directory.

## Step 7: Verify Setup

1. **Verify the Remote Connection:**
   - You should now be able to work on files located on your remote Linux machine directly from your VSCode on Windows.
   - You can open a terminal in VSCode (`Ctrl+``) and it will be connected to the remote machine.

---

You have now set up private-public key pair authentication between your Windows and Linux machines and configured VSCode to use this setup. You can securely connect to your Linux machine and manage files and projects remotely using VSCode.