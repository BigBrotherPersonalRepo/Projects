'''
Checkout page object for the Oriflame front-end autotest project.
'''
from selenium.webdriver.common.by import By
import basePage

class CheckoutPage(basePage.BasePage):

    #page elements
    CART_NAVIGATION_BUTTON = (By.XPATH, "//button[@data-testid='Checkout-@ori/checkout-basket-navigation-button']")
    EMPTY_CART_BUTTON = (By.XPATH, "//button[@data-testid='Checkout-checkout-basket-clear-basket']")
    BASKET_SECTION = (By.XPATH, "//div[@data-testid='basket-section']")
    QUANTITY_INPUT = (By.XPATH, "//input[contains(@data-testid, 'Checkout-checkout-basket-products-item-') and @value='1']")