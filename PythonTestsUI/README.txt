Front-end autotest project.
====================================
====================================

Project contains:
=================
folders:
-drivers
-->geckodriver.exe

files:
-config.py
-common.py
-basePage.py
-homePage.py
-whatsNewPage.py
-checkoutPage.py
-test.py (main)
=> ALL THESE ELEMENTS MUST BE IN SAME FOLDER!

-log.txt is created after execution of test.py and contains test result

Prerequisites:
==============
- latest version of firefox browser installed
- python environment for developing instaled 
- selenium library | command: pip istall selenium
- pytest library | command: pip install pytest

Running:
========
- test can be runned with from main project folder with command: "pytest -v -s {path to repo with tests}"

Result:
=======
- if the test was successful, message "Test successfully completed! (test.py)" is written into log.txt file in main project folder
- if not, errors are logged into log.txt file in main project folder and assertion fail message is written into console if occurs

TEST DESIGN:
==================================================================================================================================
Test is checking, if adding to bag action on webpage Oriflame.cz is working properly.
Test is using firefox browser.
==================================================================================================================================
Scenario:
            1. Initializing page objects
            2. Loading Oriflame homePage
            3. Confirmation of didomi popup with agree
            4. Clicking on "Whats new" section button (redirection on whatsNew page)
            5. Clicking on "AddToCart" button in first product box on page
            6. Clicking on "Cart" button (redirection to checkout page)
            7. Waiting when checkout page loads itself
            8. Checking if product was successfully added into basket (checking 3 elements visible only when basket has product)
                - basket section
                - empty cart button
                - quantity input with value 1 (value is representing number of products in basket)
            9. Writing successful test result into log.txt file
==================================================================================================================================

