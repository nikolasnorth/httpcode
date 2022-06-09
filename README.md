# HTTP Code CLI

## Overview

HTTP Code is a minimal command line application that displays information about HTTP status codes.

## Usage

```bash
$ httpcode <code> | list [<category_name>]
```

Valid category names are: informational, success, redirection, client-error, and server-error.

## Examples

```bash
> httpcode 200

# 200 OK
# The request has succeeded.
# 
# Learn more: https://www.httpstatuses.io/200

> httpcode list

# -----------------
# HTTP Status Codes
# -----------------
# 100 Continue
# 101 Switching Protocols
# ...

> httpcode list informational

# -----------------
# 1xx Informational
# -----------------
# 100 Continue
# 101 Switching Protocols
# 102 Processing
# 103 Early Hints
```
