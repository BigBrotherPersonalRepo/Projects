'''
BasePage class which is inherited by all page objects for the Oriflame front-end autotest project.
'''
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

class BasePage:

    #constructor
    def __init__(self, driver):
        self.driver = driver
        self.wait = WebDriverWait(self.driver, 10)

    #function for safe finding of element
    #if element is found, returns element
    #if not, writes error into log.txt file
    def safe_find_element(self, by, locator):
        try:
            element = self.driver.find_element(by, locator)
            return element
        except:
            with open("log.txt", "a") as f:
                f.write(f"Error: Element not found! || locatorType: {by}; locator: {locator}\n")
    
    #function for clicking on element
    #if clicking is correctly performed, returns nothing
    #if not, writes error into log.txt file
    def click_on_element(self, driver, locator):
        try:
            wait = WebDriverWait(driver, 10)
            wait.until(EC.element_to_be_clickable(locator))
            button = self.safe_find_element(*locator)
            button.click()
        except:
             with open("log.txt", "a") as f:
                f.write(f"Error: Element cannot be clicked on! || locator: {locator}\n")