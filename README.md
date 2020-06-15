# NOT EV Charging Station

The proposed EVCS provides a single-phase home used EVCS, which means EV can be charged with 230VAC, 10-30A power source. A 24kWh battery with a 3.3kW (15 A) charger would take less than 8 hours to fully charge.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

You will need to install **STM32CubeIDE** and **MinGW** for this project.


### Installing

- Installing STM32CubeIDE for Windows
  + [STM32CubeIDE Windows Installer](https://www.st.com/en/development-tools/stm32cubeide.html)
- Installing compiler (GCC) for host (Windows)
  + [MinGW - Minimalist GNU for Windows](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/)
  + When you see the Installation Manager Window, go to Basic Setup > right click on mingw32-gcc++.bin & msys-base-bin > Mark for Installation.
  + After that, go to Installation > Apply Changes > Apply
  + After Installing close the Installer
  + Go to Control Panel > System and Security > System > Advanced system settings > Advanced >
  Environment Variables > Under user varibles choose Path and click Edit
  + After that copy the path of your MinGW Installation ex: 'C:\MinGW\bin' and 'C:\MinGW\msys\1.0\bin'


## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
