<img height="150" src="https://raw.githubusercontent.com/tivolicloud/interface/main/logo-dark.svg" alt="Tivoli Cloud VR"/>

# https://tivolicloud.com

Tivoli Cloud VR (Tivoli) is a massive online social platform for virtual reality and desktop.

This repository contains all components needed to build our interface as well as servers.
You will find compiling support for several operating systems and architectures.

# Documentation

Documentation is available at [docs.tivolicloud.com](https://docs.tivolicloud.com). If something is missing or there's an issue, post it on our [git issues](https://git.tivolicloud.com/tivolicloud/issues/-/issues).

The JavaScript API reference can be found under [apidocs.tivolicloud.com](https://apidocs.tivolicloud.com).

We have a [Discord server](https://tivolicloud.com/discord) where you can always ask for help.

There is also detailed documentation on [our coding standards](CODING_STANDARD.md).

# License

Tivoli was [AGPLv3](https://www.gnu.org/licenses/agpl-3.0.en.html)

Built atop HFVRP Copyright 2019 High Fidelity, Inc.

# Building

All information required to build is found in the [build guide](BUILD.md).

# Running interface

You can run the interface using the launcher available at: https://tivolicloud.com/download

If you're using a self-compiled version, you can set the build location in the launcher under the developer menu.

If you want to run Tivoli without the launcher, run:

```cmd
interface.exe --tokens [current access token]
```

You can find your access token in the launcher's developer menu. Please don't share it and keep it safe!

# Running your own server

There is advanced guide on our docs on [how to host a world](https://docs.tivolicloud.com/worlds/host-a-world-advanced/)

The server is freshly available for Docker on our [container registry](https://git.tivolicloud.com/tivolicloud/interface/container_registry) which we recommend. Alternatively less fresh on [Docker hub](https://hub.docker.com/r/tivolicloud/server).

If you want to run a self-compiled version, refer to:

-   https://git.tivolicloud.com/tivolicloud/interface/-/tree/main/docker/server
-   https://git.tivolicloud.com/tivolicloud/interface/-/tree/main/.gitlab/deploy.gitlab-ci.yml
