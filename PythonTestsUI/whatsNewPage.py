'''
Whats new page object for the Oriflame front-end autotest project.
'''
from selenium.webdriver.common.by import By
import basePage

class WhatsNewPage(basePage.BasePage):

    #page elements
    ADD_TO_CART_BUTTON = (By.XPATH, "//*[name()='svg' and @data-testid='QuickBuyOutlinedIcon']")
    BAG_BUTTON = (By.XPATH, "//a[@data-testid='Presentation-top-area-shopping-bag-icon-root']")
