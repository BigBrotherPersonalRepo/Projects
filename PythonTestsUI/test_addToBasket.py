'''
Test file for the Oriflame front-end autotest project.
Contains main test execution.
'''
import config
import common
import homePage
import whatsNewPage
import checkoutPage
import pytest

@pytest.fixture()
def set_up():
    print("Starting tests execution..")
    yield
    print(" Execution ends..")

def test_add_to_basket(set_up):
    #initialization of the PageObjects
    home_page = homePage.HomePage(config.browser)
    whats_new_page = whatsNewPage.WhatsNewPage(config.browser)
    checkout_page = checkoutPage.CheckoutPage(config.browser)

    #driver positioning on homepage
    config.browser.get(config.url)

    #confirming of didomi and loading whats new page from homepage
    home_page.click_on_element(config.browser, home_page.CONFIRM_DIDOMI_BUTTON, "test_add_to_basket")
    home_page.click_on_element(config.browser, home_page.WHATS_NEW_BUTTON, "test_add_to_basket")

    #adding product into a basket and loading checkout page from whats new page
    whats_new_page.click_on_element(config.browser, whats_new_page.ADD_TO_CART_BUTTON, "test_add_to_basket")
    whats_new_page.click_on_element(config.browser, whats_new_page.BAG_BUTTON, "test_add_to_basket")

    #waiting for loading checkout page and checking if item was correctly added into a basket with assertions
    common.wait_for_element(config.browser, checkout_page.CART_NAVIGATION_BUTTON, "test_add_to_basket")
    common.check_element_visible(config.browser, checkout_page.BASKET_SECTION, "test_add_to_basket")
    common.check_element_visible(config.browser, checkout_page.EMPTY_CART_BUTTON, "test_add_to_basket")
    common.check_element_visible(config.browser, checkout_page.QUANTITY_INPUT, "test_add_to_basket")

    #writing successful result into log.txt
    with open("log.txt", "a") as f:
        f.write(f"Test successfully completed! (test.py)\n")