'''
File which contains shared verification functions for the Oriflame front-end autotest project.
'''
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

#function for waiting until element is visible
#if element is visible, returns nothing
#if not, writes error into log.txt file
def wait_for_element(driver, locator, test_name):
        try:
            wait = WebDriverWait(driver, 10)
            wait.until(EC.presence_of_element_located(locator))
        except:
             with open("log.txt", "a") as f:
                f.write(f"\n\nTest name = {test_name}:\n")
                f.write(f"Error: Element is not presented! || locator: {locator}\n")

#function which checks if element is visible with assertion
#if element is visible, returns nothing
#if not, writes error into log.txt file and assertion ends testing with message in console
def check_element_visible(driver, locator, test_name):
    try:
        wait = WebDriverWait(driver, 10)
        wait.until(EC.presence_of_element_located(locator))
        found = True
    except:
        found = False
        with open("log.txt", "a") as f:
                f.write(f"\n\nTest name = {test_name}:\n")
                f.write(f"Error: Element is not visible! || locator: {locator}\n")
    assert found