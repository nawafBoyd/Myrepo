<?php

/**
 * Form constructor for the provider settings form.
 *
 * @see uc_multi_currency_provider_localized_settings_form_submit()
 *
 * @ingroup forms
 */
function uc_multi_currency_provider_localized_settings_form($form, &$form_state) {
  $form = array();

  $currencies = array(0 => t('undecided'));
  foreach (_uc_multi_currency_currency_load() as $currency) {
    $currencies[$currency->cid] = check_plain($currency->name .' ('. $currency->cid .')');
  }

  foreach (language_list() as $lid => $language) {
    $form['uc_multi_currency_use_localized_'. $lid] = array(
      '#type' => 'select',
      '#title' => t($language->name),
      '#options' => $currencies,
      '#default_value' => variable_get('uc_multi_currency_use_localized_'. $lid),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Form submission handler for uc_multi_currency_provider_localized_settings_form().
 */
function uc_multi_currency_provider_localized_settings_form_submit($form, &$form_state) {
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
function uc_multi_currency_provider_localized_callback() {
  global $language;

  return variable_get('uc_multi_currency_use_localized_'. $language->language, NULL);
}
