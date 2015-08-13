<?php

/**
 * Form constructor for the currency usage form.
 *
 * Path: admin/store/settings/currency/usage
 *
 * @see uc_multi_currency_menu()
 * @see uc_multi_currency_currency_usage_form_submit()
 * @see theme_uc_multi_currency_currency_usage_form()
 *
 * @ingroup forms
 */
function uc_multi_currency_currency_usage_form($form, &$form_state) {
  $providers = _uc_multi_currency_currency_usage_provider_info();
  $enabled = variable_get('uc_multi_currency_providers_enable', array());
  $weights = variable_get('uc_multi_currency_providers_weight', array());

  $form = array(
    '#submit' => array('uc_multi_currency_currency_usage_form_submit'),
    '#theme' => 'uc_multi_currency_currency_usage_form',
    '#currency_usage_providers' => $providers,
    '#tree' => TRUE,
  );

  foreach ($providers as $id => $provider) {
    if (!isset($weights[$id])) {
      $default = is_numeric($provider) ? $provider : 0;
      $weights[$id] = isset($provider['weight']) && is_numeric($provider['weight']) ? $provider['weight'] : $default;
    }
  }
  asort($weights);

  foreach ($weights as $id => $weight) {
    if (isset($providers[$id])) {
      $provider = $providers[$id];
      $form['weight'][$id] = array(
        '#type' => 'weight',
        '#title' => t('Weight for @title', array('@title' => $provider['name'])),
        '#title_display' => 'invisible',
        '#default_value' => $weight,
        '#attributes' => array('class' => array("currency-usage-provider-weight")),
      );
      $form['title'][$id] = array(
        '#type' => 'markup',
        '#markup' => check_plain($provider['name']),
      );
      $form['enabled'][$id] = array(
        '#type' => 'checkbox',
        '#title' => t('@title currency usage provider', array('@title' => $provider['name'])),
        '#title_display' => 'invisible',
        '#default_value' => isset($enabled[$id]) && $enabled[$id],
      );
      $form['description'][$id] = array(
        '#type' => 'markup',
        '#markup' => filter_xss_admin($provider['description']),
      );
      $form['operation'][$id] = array(
        '#type' => 'link',
        '#title' => t('configure'),
        '#href' => 'admin/store/settings/currency/usage/configure/'. $id,
      );
    }
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

/**
 * Form submission handler for uc_multi_currency_currency_usage_form().
 */
function uc_multi_currency_currency_usage_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $providers = $form['#currency_usage_providers'];
  $enabled = array();
  $weights = array();
  foreach ($providers as $id => $provider) {
    $enabled[$id] = $values['enabled'][$id];
    $weights[$id] = $values['weight'][$id];
  }
  asort($weights);
  variable_set('uc_multi_currency_providers_enable', $enabled);
  variable_set('uc_multi_currency_providers_weight', $weights);
  $form_state['redirect'] = 'admin/store/settings/currency/usage';
  drupal_set_message(t('Currency selection configuration saved.'));
}

/**
 * Returns HTML for a currency usage configuration form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_uc_multi_currency_currency_usage_form($variables) {
  $form = $variables['form'];
  $rows = array();
  $output = '';

  foreach ($form['title'] as $id => $element) {
    if (is_array($element) && element_child($id)) {
      $row = array(
        'data' => array(
          '<strong>' . drupal_render($form['title'][$id]) . '</strong>',
          drupal_render($form['description'][$id]),
          drupal_render($form['enabled'][$id]),
          drupal_render($form['weight'][$id]),
        ),
        'class' => array('draggable'),
      );
      $row['data'][] = drupal_render($form['operation'][$id]);
      $rows[] = $row;
    }
  }

  $header = array(
    array('data' => t('Detection method')),
    array('data' => t('Description')),
    array('data' => t('Enabled')),
    array('data' => t('Weight')),
    array('data' => t('Operations')),
  );

  $variables = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => "currency-usage-negotiation-providers"),
  );
  $table = theme('table', $variables);
  $table .= drupal_render_children($form);

  drupal_add_tabledrag("currency-usage-negotiation-providers", 'order', 'sibling', "currency-usage-provider-weight");

  $output .= '<div class="form-item">'. $table .'</div>';
  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Page callback to set the currency for the current user.
 *
 * Path: uc_multi_currency/%/set
 *
 * @param string $cid
 *   The currency to set.
 */
function uc_multi_currency_set_currency($cid) {
  global $user;

  $_SESSION['uc-multi-currency-'. $user->uid] = $cid;
  $currency = _uc_multi_currency_currency_load($cid);
//  drupal_set_message(t('Your currency has been set to %currency.', array('%currency' => $currency->name)));
  $destination = drupal_get_destination();
  drupal_goto($destination['destination']);
}
