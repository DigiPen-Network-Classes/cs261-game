# CS 261: Assignment 4 - Game Server and Client

This is the assignment that brings the C++ Game Client/Server and the Node.js User Service together.
The client authenticates with your User Service. The client then calls a new endpoint to get a URL and
token for a Game Server. the Game Server then validates the token, and play commences..

## Prerequisites

You will need the Microsoft package manager [vcpkg](https://github.com/Microsoft/vcpkg) -- 
use that to install the [cpprestsdk](https://github.com/microsoft/cpprestsdk) and [openssl](https://vcpkg.io/en/package/openssl.html) libraries.

### Installing vcpkg

```pwsh
# wherever you like to put this sort of thing:
cd C:\users\your-name\source\repos
git clone https://github.com/Microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg integrate install
```

### Installing Packages

```pwsh
./vcpkg install cpprestsdk
./vcpkg install cpprestsdk:x86-windows

./vcpkg install openssl
./vcpkg install openssl:x86-windows
```

## x86 Warning!

The CProcessing libraries included here are x86 (32-bit) only. I will eventually update the package to use the new version,
but until that happens -- the "CS261_Assignment4" solution is currently setup to build only x86. This means that 
you *must* have the 32-bit versions of `cpprestsdk` and `openssl` installed! (By default, vcpkg installs
the version that matches your architecture, which as this is 2024 is almost guaranteed to be x64
(or, perhaps ARM or something more exotic...but certainly not x86).

# Creating the Test User

First, make sure your Assignment 3 User Service is running. Then use curl to create a test user:

```
# verbose output to see the result and verify the 200 response:

curl -vv http://localhost:3100/api/v1/users \
-d '{ "username": "test_user", "password": "test_password", "avatar": "test_avatar" }' \
-H 'content-type: application/json'
```

You should see a successful response (something something `200 OK`) and the user json response:
```json
{"id":"50b5d00900474eafaa7af60f", "username":"test_user", "avatar":"test_avatar","password":"test_password"}
```

# User Service Changes Required

## New endpoint: POST /api/v1/connect

Requires authentication (a valid session). 

### Request Body

```json
{
  "session": "valid-session-token", 
  "game_type": "some-game-type"
}
```

### Response Body

This returns the user's information, the port to connect to the game server, and a token used by the game server.

Example:
```json
{
  "username": "test_user",
  "avatar": "test_avatar",
  "game_port": 4200,
  "token": "aabbccddee"
}
```

### Creating the Token

Start by creating the plaintext token by concatenating these strings -- remember that the order must be the same as on the Game Server!
* username
* avatar
* game_type
* shared_secret

Then generate the hash of that string, using the `crypto` lib in Node.js:
```js
import crypto from 'crypto';
const token = crypto.createHash('sha256').update(rawToken).digest('base64');
```

## New .env values

There are two new configuration values you'll need to add to the .env file

```env
SHARED_SECRET=cs261secret
GAME_PORT=4200
```

Your node.js User Service should read those values from the environment, as we have done for other configurable settings 
in previous assignments.


