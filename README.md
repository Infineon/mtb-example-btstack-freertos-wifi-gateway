# Bluetooth&reg; LE IoT gateway

This code example demonstrates implementing a Bluetooth&reg; IoT gateway using the MQTT client library and Bluetooth&reg; host stack for Infineon connectivity devices. The MQTT client library uses the AWS IoT device SDK that includes an MQTT 3.1.1 client as well as libraries specific to AWS IoT such as Thing Shadows. The Bluetooth&reg; Mesh stack runs with FreeRTOS in the server and client model.

This example has two main parts: MQTT and Mesh. The MQTT client RTOS task establishes a connection with the configured MQTT broker (AWS IoT core in this example), and with the publisher and subscriber for two-way communication with the cloud using MQTT topics. The Mesh is initialized with a server and client model with the GATT provisioner service.
It establishes communication with other nodes ([Light Dimmable](https://github.com/Infineon/mtb-example-btsdk-mesh-demo-light-dimmable) and [On Off Switch](https://github.com/Infineon/mtb-example-btsdk-mesh-demo-on-off-switch)).

[View this README on GitHub.](https://github.com/Infineon/mtb-example-btstack-freertos-wifi-gateway)

[Provide feedback on this code example.](https://cypress.co1.qualtrics.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyMzA4NTgiLCJTcGVjIE51bWJlciI6IjAwMi0zMDg1OCIsIkRvYyBUaXRsZSI6IkJsdWV0b290aCZyZWc7IExFIElvVCBnYXRld2F5IiwicmlkIjoiYXNyYSIsIkRvYyB2ZXJzaW9uIjoiMi4wLjAiLCJEb2MgTGFuZ3VhZ2UiOiJFbmdsaXNoIiwiRG9jIERpdmlzaW9uIjoiTUNEIiwiRG9jIEJVIjoiSUNXIiwiRG9jIEZhbWlseSI6IkJUQUJMRSJ9)

## Requirements

- [ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) v3.0 or later (tested with v3.0)
- Board support package (BSP) minimum required version: 4.0.0
- Programming language: C
- Associated parts: All [PSoC&trade; 6 MCU](https://www.infineon.com/cms/en/product/microcontroller/32-bit-psoc-arm-cortex-microcontroller/psoc-6-32-bit-arm-cortex-m4-mcu) parts, [AIROC&trade; CYW43012 Wi-Fi & Bluetooth&reg; combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/wi-fi-4-802.11n/cyw43012), [AIROC&trade; CYW43439 Wi-Fi & Bluetooth&reg; combo chip](https://www.infineon.com/cms/en/product/wireless-connectivity/airoc-wi-fi-plus-bluetooth-combos/wi-fi-4-802.11n/cyw43439)


## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; embedded compiler v10.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`


## Supported kits (make variable 'TARGET')

- [PSoC&trade; 62S2 Wi-Fi Bluetooth&reg; pioneer kit](https://www.infineon.com/CY8CKIT-062S2-43012) (`CY8CKIT-062S2-43012`) – Default value of `TARGET`
- [PSoC&trade; 62S2 evaluation kit](https://www.infineon.com/CY8CEVAL-062S2) (`CY8CEVAL-062S2-MUR-43439M2`)

## Hardware setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

## Software setup

1. Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en).

2. Install the [Mesh Client Controller application](https://www.infineon.com/cms/en/design-support/tools/sdk/wireless-connectivity-bluetooth-mesh-helper-applications/).

**Note:** Android Mesh Client Controller application functionality depends on the availability of a compatible Bluetooth&reg; stack and permissions on the Android handset device.


## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox&trade; Application**). This launches the [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

The "project-creator-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br />

The following example clones the "[IoT Gateway](https://github.com/Infineon/mtb-example-btstack-freertos-wifi-gateway)" application with the desired name "IoTgateway" configured for the *CY8CKIT-062S2-43012* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id CY8CKIT-062S2-43012 --app-id mtb-example-btstack-freertos-wifi-gateway --user-app-name IoTgateway --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can invoke the Library Manager GUI tool from the terminal using `make library-manager` command or use the Library Manager CLI tool "library-manager-cli" to change the BSP.

The "library-manager-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--add-bsp-name` | Name of the BSP that should be added to the application | Required
`--set-active-bsp` | Name of the BSP that should be as active BSP for the application | Required
`--add-bsp-version`| Specify the version of the BSP that should be added to the application if you do not wish to use the latest from manifest | Optional
`--add-bsp-location`| Specify the location of the BSP (local/shared) if you prefer to add the BSP in a shared path | Optional

<br />

Following example adds the CY8CEVAL-062S2-MUR-43439M2 BSP to the already created application and makes it the active BSP for the app:

   ```
   library-manager-cli --project "C:/mtb_projects/IoTgateway" --add-bsp-name CY8CEVAL-062S2-MUR-43439M2 --add-bsp-version "latest-v4.X" --add-bsp-location "local"

   library-manager-cli --project "C:/mtb_projects/IoTgateway" --set-active-bsp APP_CY8CEVAL-062S2-MUR-43439M2
   ```

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP, and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br />

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>


## Operation

1. Boards required to run this example:

   1. Connect the CY8CKIT-062S2-43012 board to your PC using the provided USB cable through the KitProg3 USB connector.

   2. Connect any of two AIROC™ Bluetooth&reg; boards (for example, CYW920835M2EVB-01 or CYBT-213043-MESH) to your PC using the provided USB cable.This boards act as Node1 and Node2.

2. Modify the user configuration files in the *configs* directory as follows:

      1. Set the Wi-Fi credentials in *configs/wifi_config.h*: Modify the `WIFI_SSID`, `WIFI_PASSWORD`, and `WIFI_SECURITY` macros to match with that of the Wi-Fi network that you want to connect.

      2. Set up the MQTT client and configure the credentials in *configs/mqtt_client_config.h* as follows:

         1. Set up the MQTT device (also known as a *Thing*) in the AWS IoT core as described in the [Getting started with AWS IoT tutorial](https://docs.aws.amazon.com/iot/latest/developerguide/iot-gs.html).

         2. Set `MQTT_BROKER_ADDRESS` to your custom endpoint on the settings page of the AWS IoT console. This has the format `ABCDEFG1234567.iot.<region>.amazonaws.com`.

         3. Download the following certificates and keys that are created and activated in the previous step:
               - A certificate for the AWS IoT Thing - *xxxxxxxxxx.cert.pem*
               - A public key - *xxxxxxxxxx.public.key*
               - A private key - *xxxxxxxxxx.private.key*
               - Root CA "RSA 2048 bit key: Amazon Root CA 1" for AWS IoT from [CA certificates for server authentication](https://docs.aws.amazon.com/iot/latest/developerguide/server-authentication.html#server-authentication-certs).

         4. Using these certificates and keys, enter the following parameters in *mqtt_client_config.h* in privacy-enhanced mail (PEM) format:
               - `CLIENT_CERTIFICATE` - *xxxxxxxxxx.cert.pem*
               - `CLIENT_PRIVATE_KEY` - *xxxxxxxxxx.private.key*
               - `ROOT_CA_CERTIFICATE` - Root CA certificate

            You can either convert the values to strings manually using the format shown in *mqtt_client_config.h* or you can use the HTML utility available [here](https://github.com/Infineon/amazon-freertos/blob/master/tools/certificate_configuration/PEMfileToCString.html) to convert the certificates and keys from PEM format to C string format. You need to clone the repository from GitHub to use the utility.

      3. (Optional): Modify the configuration macros in the following files according to your application:
         - *configs/core_mqtt_config.h* used by the [MQTT library](https://github.com/Infineon/mqtt)
         - *configs/FreeRTOSConfig.h*

3. Open a terminal program and select the *KitProg3 COM port* for CY8CKIT-062S2-43012 and *WICED PUART* for CYW920835M2EVB-01. Set the serial port parameters to 8N1 and 115200 baud for both boards.

4. Program Node1 (for example, CYW920835M2EVB-01).

   See the [Demo Light Dimmable](https://github.com/Infineon/mtb-example-btsdk-mesh-demo-light-dimmable) code example for information on building and programming the board. After programming is complete, provision this node with the Mesh Client Controller app.

5. Program Node2 (for example, CYBT-213043-MESH).

   See the [Demo Switch On Off](https://github.com/Infineon/mtb-example-btsdk-mesh-demo-on-off-switch) code example for information on building and programming the board. After programming is complete, provision this node with the Mesh Client Controller app.

6. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE for ModusToolbox&trade; software</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
   </details>

   <details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. The default toolchain is specified in the application's Makefile but you can override this value manually:
      ```
      make program TOOLCHAIN=<toolchain>
      ```

      Example:
      ```
      make program TOOLCHAIN=GCC_ARM
      ```
   </details>

7. After programming, the application starts automatically. Observe the messages on the UART terminal, and wait for the device to make all the required connections.

   **Figure 1. Terminal output on program startup**

   ![](images/app_init_console.png)
   
8. Confirm that the User LED1 blinks at approximately 2 Hz which indicates that the gateway node is advertising with the name of "IoT Gateway".

9. Once the initialization is complete, the client establishes connection with the AWS cloud and starts advertising with the name "IoT Gateway". You need to provision the IoT gateway and other nodes.

   **Figure 2. Creating Mesh network**

   ![](images/create_mesh_network.png)

   **Figure 3. Provision the gateway**

   ![](images/prov_gateway_node.png)

   **Figure 4. Provision the Dimmable Light**

   ![](images/prov_light_node.png)

   **Figure 5. Provision the On Off Switch**

   ![](images/prov_switch_node.png)

   **Figure 6. MQTT and GATT DB connections**

   ![](images/app_connect_console.png)

   The Dimmable Light and On Off Switch Mesh nodes publish the data to the Mesh network; the IoT Gateway node subscribes to the data from the Mesh network.

   Press the user button (SW2) to publish the values on the topic to the AWS cloud. Press and hold the user button (SW2) for more than 5 seconds to perform a factory reset. Factory reset is recommended before flashing any newer firmware.

   **Figure 7. App console output**

   ![](images/app_connect_console.png)

   Toggling the user button on the On Off Switch node changes the On Off status value. It is published to the cloud from the IoT Gateway node. Swicth level and light level values are maintained in the AWS device shadow file.

   **Figure 8. AWS device shadow**

   ![](images/aws_shadow_data.png)

   See the [AWS device shadow](https://docs.aws.amazon.com/iot/latest/developerguide/device-shadow-document.html) page for details on using the device shadow service.

   The user can obtain the node information in the cloud by publishing the SET/GET commands to the device on the **IOT_GATEWAY/mesh_devices** topic.

   The Light Node and Switch Node status can be read from the cloud with the `GET NODE` command. The Dimmable Light node brightness can be controlled from the cloud with the `SET LIGHT` command.

      Example:
      ```
      GET NODE
      SET LIGHT 6
      ```
   **Figure 9. Publish to device from AWS**

   ![](images/aws_publish_control.png)

10. Press and hold the user button (SW2) for more than 5 seconds to perform a factory reset. Factory reset is recommended before flashing any newer firmware.

Note that the device is in unprovisioned state after a factory reset. You need to reprovision the node again (follow instructions from Step 9).

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application Name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**. For details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide).

**Note:** **(Only while debugging)** On the CM4 CPU, some code in `main()` may execute before the debugger halts at the beginning of `main()`. This means that some code executes twice – once before the debugger stops execution, and again after the debugger resets the program counter to the beginning of `main()`. See [KBA231071](https://community.infineon.com/docs/DOC-21143) to learn about this and for the workaround.


## Design and implementation

The IoT Bluetooth&reg; gateway application implements Mesh server and client models as two elements. The elements subscribe the messages from the Light Dimmable (server) and On Off Switch (client) Mesh nodes. This application talks to the cloud over MQTT with topic subscribe and publish operations. The button ISR is implemented for the user to publish the data and to reset the node.

UART is used for console logs. Mesh traces can be enabled via the `WICED_BT_MESH_TRACE_ENABLE` macro set in the Makefile; User LED1 is used for showing the provision status and User LED2 is for application use.

See the Bluetooth&reg; Mesh API guide (*{mtb_shared}/ble-mesh/release-{version}/docs/api_reference_manual.html*) for more information about Bluetooth&reg; Mesh APIs available as part of BTStack SDK.

**Figure 10. Design**

![](images/iot_gateway_flow.png)


### Resources and settings

**Table 1. Application resources**

 Resource  |  Alias/object     |    Purpose
 :-------- | :-------------    | :------------
 UART (HAL)|cy_retarget_io_uart_obj| UART HAL object used by Retarget-IO for the Debug UART port
 GPIO (HAL)    | CYBSP_USER_LED     | User LED
 GPIO (HAL)    | CYBSP_USER_BTN     | User button

<br />

## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  | [AN228571](https://www.infineon.com/AN228571) – Getting started with PSoC&trade; 6 MCU on ModusToolbox&trade; software <br /> [AN215656](https://www.infineon.com/AN215656) – PSoC&trade; 6 MCU: Dual-CPU system design
Code examples  | [Using ModusToolbox&trade; software](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub <br /> [Using PSoC&trade; Creator](https://www.infineon.com/cms/en/design-support/software/code-examples/psoc-3-4-5-code-examples-for-psoc-creator)
Device documentation | [PSoC&trade; 6 MCU datasheets](https://documentation.infineon.com/html/psoc6/bnm1651211483724.html) <br /> [PSoC&trade; 6 technical reference manuals](https://documentation.infineon.com/html/psoc6/zrs1651212645947.html)
Development kits | Select your kits from the [evaluation board finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board)
Libraries on GitHub  | [mtb-pdl-cat1](https://github.com/Infineon/mtb-pdl-cat1) – PSoC&trade; 6 peripheral driver library (PDL)  <br /> [mtb-hal-cat1](https://github.com/Infineon/mtb-hal-cat1) – Hardware abstraction layer (HAL) library <br /> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port
Middleware on GitHub | [mqtt](https://github.com/Infineon/mqtt) – MQTT client library and documents <br> [wifi-connection-manager](https://github.com/Infineon/wifi-connection-manager) – Wi-Fi connection manager (WCM) library and documents <br> [wifi-mw-core](https://github.com/Infineon/wifi-mw-core)  –  Wi-Fi middleware core library and documents <br> [freeRTOS](https://github.com/Infineon/freertos) – FreeRTOS library and documents <br> [psoc6-middleware](https://github.com/Infineon/modustoolbox-software#psoc-6-middleware-libraries) – Links to all PSoC&trade; 6 MCU middleware
Tools  | [Eclipse IDE for ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth&reg; connectivity devices. <br /> [PSoC&trade; Creator](https://www.infineon.com/cms/en/design-support/tools/sdk/psoc-software/psoc-creator/) – IDE for PSoC&trade; and FM0+ MCU development

<br />

## Other resources

Infineon provides a wealth of data at www.infineon.com to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC&trade; 6 MCU devices, see [How to design with PSoC&trade; 6 MCU - KBA223067](https://community.infineon.com/docs/DOC-14644) in the Infineon Developer community.


## Document history

Document title: *CE230858* – *Bluetooth&reg; LE IoT gateway*

 Version | Description of change
 ------- | ---------------------
|1.1.0   | New code example
|2.0.0   | Updated to support ModusToolbox&trade; software v3.0 and BSPs v4.X   |
<br />



---------------------------------------------------------

© Cypress Semiconductor Corporation, 2020-2022. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates ("Cypress").  This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br />
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br />
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit www.infineon.com. Other names and brands may be claimed as property of their respective owners.
