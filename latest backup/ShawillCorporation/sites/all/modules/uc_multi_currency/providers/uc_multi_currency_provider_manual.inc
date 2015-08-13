<?php

/**
 * Form constructor for the provider settings form.
 *
 * @see uc_multi_currency_provider_manual_settings_form_submit()
 *
 * @ingroup forms
 */
function uc_multi_currency_provider_manual_settings_form($form, &$form_state) {
  $form = array();

  $form['none'] = array(
    '#type' => 'markup',
    '#markup' => '<p>'. t('There are no configurable settings.') .'</p>',
  );
  $form['cancel'] = array(
    '#type' => 'link',
    '#href' => 'admin/store/settings/currency/usage',
    '#title' => t('Cancel'),
  );

  return $form;
}

/**
 * Form submission handler for uc_multi_currency_provider_manual_settings_form().
 */
function uc_multi_currency_provider_manual_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  foreach ($values as $key => $value) {
    variable_set($key, $value);
  }
  $form_state['redirect'] = 'admin/store/settings/currency/usage';
}

/**
 * Returns
 * - a {uc_multi_currency}.cid currency identifier if it can decide which currency to use
 * - NULL if it cannot decide
 */
function uc_multi_currency_provider_manual_callback() {
  global $user;

  return isset($_SESSION['uc-multi-currency-'. $user->uid]) ? $_SESSION['uc-multi-currency-'. $user->uid] : 0;
}
