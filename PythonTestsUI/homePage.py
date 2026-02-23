'''
HomePage page object for the Oriflame front-end autotest project.
'''
from selenium.webdriver.common.by import By
import basePage

class HomePage(basePage.BasePage):

    #page elements
    WHATS_NEW_BUTTON = (By.XPATH, "//a[@data-testid='Presentation-whats-new-button-right']")
    CONFIRM_DIDOMI_BUTTON = (By.XPATH, "//button[@id='didomi-notice-agree-button']")