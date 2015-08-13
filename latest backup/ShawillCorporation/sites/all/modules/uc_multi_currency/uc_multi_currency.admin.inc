<?php

/**
 * Form constructor for the currency list form.
 *
 * Path: admin/store/settings/currency
 *
 * @see uc_multi_currency_menu()
 * @see theme_uc_multi_currency_currency_list_form()
 * @see uc_multi_currency_currency_list_form_submit()
 *
 * @ingroup forms
 */
function uc_multi_currency_currency_list_form($form, &$form_state) {
  $files = _uc_multi_currency_import_list();

  $rows = array();
  $currencies = _uc_multi_currency_currency_load();
  foreach ($currencies as $currency) {
    $row = array();
    if ($currency->enabled) {
      $row['name'] = check_plain($currency->name);
    }
    else {
      $row['name'] = array('data' => check_plain($currency->name), 'style' => 'color:silver');
    }
    $row['cid'] = check_plain($currency->cid);
    $row['positive'] = check_plain($currency->positive) .' / '. check_plain($currency->negative);
    $ops = array();
    $ops[] = l($currency->enabled ? t('disable') : t('enable'), 'admin/store/settings/currency/'. $currency->cid .'/enable');
    $ops[] = l(t('edit'), 'admin/store/settings/currency/'. $currency->cid .'/edit');
    $ops[] = l(t('delete'), 'admin/store/settings/currency/'. $currency->cid .'/delete');
    $row[] = implode(' ', $ops);

    $rows[] = $row;
    unset($files[$currency->cid]);
  }

  $import_list = array();
  foreach ($files as $file) {
    $import_list[$file['file']] = $file['file'];
  }

  if (!empty($import_list)) {
    ksort($import_list);

    $form['currency_import'] = array(
      '#type' => 'fieldset',
      '#title' => t('Import currencies'),
      '#collapsed' => TRUE,
      '#collapsible' => TRUE,
    );

    $form['currency_import']['text'] = array(
      '#markup' => '<p>'. t('To import new currency data, select it in the list and click the import button. If you are using a custom or contributed import file, it must be placed in the Ubercart folder contrib/uc_multi_currency/currencies.') .'</p>',
    );
    $form['currency_import']['import_file'] = array(
      '#type' => 'select',
      '#title' => t('Currency'),
      '#options' => $import_list,
      '#multiple' => TRUE,
      '#size' => min(10, count($import_list)),
    );
    $form['currency_import']['actions'] = array('#type' => 'actions');
    $form['currency_import']['actions']['import_button'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
    );
  }

  $header = array(
    t('Code'),
    t('Name'),
    t('Positive / Negative'),
    array('data' => t('Operations'), 'colspan' => '3'),
  );

  $form['currency_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No currencies are defined.'),
  );

  return $form;
}

/**
 * Returns an array of currency files that can be installed.
 */
function _uc_multi_currency_import_list() {
  $dir = drupal_get_path('module', 'uc_multi_currency') .'/currencies/';

  $currencies = array();
  if (is_dir($dir)) {
    if ($dh = opendir($dir)) {
      while (($file = readdir($dh)) !== FALSE) {
        switch (filetype($dir . $file)) {
          case 'file':
            $path = pathinfo($file);
            if ($path['extension'] == 'cif') {
              $cid = $path['filename'];
              if (!isset($currencies[$cid])) {
                $currencies[$cid]['cid'] = $cid;
                $currencies[$cid]['file'] = $file;
              }
            }
            break;
        }
      }
      closedir($dh);
    }
  }

  return $currencies;
}

/**
 * Form submission handler for uc_multi_currency_currency_list_form().
 *
 * @see uc_multi_currency_currency_list_form()
 */
function uc_multi_currency_currency_list_form_submit($form, &$form_state) {
  $files = $form_state['values']['import_file'];

  foreach ($files as $file) {
    if (_uc_multi_currency_import($file)) {
      drupal_set_message(t('Currency file @file imported.', array('@file' => $file)));
    }
    else {
      drupal_set_message(t('Currency file @file could not import or had no install function.', array('@file' => $file)), 'error');
    }
  }

  cache_clear_all('_uc_multi_currency_currency_load', 'cache');
}

/**
 * Imports an Ubercart currency file by filename.
 *
 * @param $file
 *   The filename of the currency to import.
 *
 * @return boolean
 *   TRUE or FALSE indicating whether or not the currency was imported.
 */
function _uc_multi_currency_import($file) {
  require_once(drupal_get_path('module', 'uc_multi_currency') .'/currencies/'. $file);

  $path = pathinfo($file);
  $func = 'uc_multi_currency_'. $path['filename'] .'_install';
  if (function_exists($func)) {
    return $func();
  }
  return FALSE;
}

/**
 * Form constructor for the currency edit form.
 *
 * Path: admin/store/settings/currency/add
 * Path: admin/store/settings/currency/%/edit
 *
 * @param string $cid
 *   (Optional) The currency to edit.
 *
 * @see uc_multi_currency_menu()
 * @see uc_multi_currency_currency_edit_form_submit()
 *
 * @ingroup forms
 */
function uc_multi_currency_currency_edit_form($form, &$form_state, $cid = NULL) {
  if (isset($cid)) {
    $currency = _uc_multi_currency_currency_load($cid);
    $form['cid_value'] = array(
      '#type' => 'hidden',
      '#value' => $cid,
    );
    drupal_set_title(t('Edit currency %name', array('%name' => check_plain($currency->name))), PASS_THROUGH);
  }
  else {
    drupal_set_title(t('Add currency'));
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('User readable name of the currency.'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#default_value' => isset($currency->name) ? check_plain($currency->name) : '',
  );
  $form['cid'] = array(
    '#type' => 'textfield',
    '#title' => t('Alphabetic code'),
    '#description' => t('Alphabetic code as specified by the <a href="http://en.wikipedia.org/wiki/ISO_4217">ISO 4217 standard.</a> Exactly three letters.'),
    '#required' => TRUE,
    '#maxlength' => 3,
    '#default_value' => isset($currency->cid) ? check_plain($currency->cid) : '',
    '#element_validate' => array('uc_multi_currency_currency_edit_form_cid_validate'),
  );
  $form['pattern'] = array(
    '#type' => 'fieldset',
    '#title' => t('Patterns'),
    '#description' => '<p>'. t('Six or more # characters denote the amount. Use decimal and grouping separators inside the amount as necessary. Prepend or append the currency symbol with or without space, as required. Examples:') .'</p>' .
      '<ul><li>$#,###.##.</li><li>€#.###,##.</li></ul>',
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
    );
  $form['pattern']['positive'] = array(
    '#type' => 'textfield',
    '#title' => t('Display pattern for positive values'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#default_value' => isset($currency->positive) ? check_plain($currency->positive) : '¤#,###.##',
  );
  $form['pattern']['negative'] = array(
    '#type' => 'textfield',
    '#title' => t('Display pattern for negative values'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#default_value' => isset($currency->negative) ? check_plain($currency->negative) : '-¤#,###.##',
  );

  $form['symbol'] = array(
    '#type' => 'hidden',
    '#value' => '$',
  );
  $form['group_char'] = array(
    '#type' => 'hidden',
    '#value' => ',',
  );
  $form['dec_char'] = array(
    '#type' => 'hidden',
    '#value' => '.',
  );
  $form['prec'] = array(
    '#type' => 'hidden',
    '#value' => 2,
  );
  $form['prefix'] = array(
    '#type' => 'hidden',
    '#value' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Form submission handler for uc_multi_currency_currency_edit_form().
 */
function uc_multi_currency_currency_edit_form_submit($form, &$form_state) {
  $currency = isset($form['cid_value']['#value']) ? _uc_multi_currency_currency_load($form['cid_value']['#value']) : new stdClass();
  $currency->cid = strtoupper($form_state['values']['cid']);
  $currency->name = $form_state['values']['name'];
  $currency->positive = $form_state['values']['positive'];
  $currency->negative = $form_state['values']['negative'];
  $currency->enabled = 1;
  $currency->symbol = $form_state['values']['symbol'];
  $currency->group_char = $form_state['values']['group_char'];
  $currency->dec_char = $form_state['values']['dec_char'];
  $currency->prec = $form_state['values']['prec'];
  $currency->prefix = $form_state['values']['prefix'];
  _uc_multi_currency_currency_save($currency);
  cache_clear_all('_uc_multi_currency_currency_load', 'cache');
  drupal_set_message(t('The currency %name has been saved.', array('%name' => $currency->name)));
  $form_state['redirect'] = 'admin/store/settings/currency';
}

/**
 * Element validation handler for uc_multi_currency_currency_edit_form().
 */
function uc_multi_currency_currency_edit_form_cid_validate($element, $form, &$form_state) {
  if (!preg_match('/[a-z][a-z][a-z]/i', $element['#value'])) {
    form_error($element, t('The alphabetic code should be exactly three letters.'));
  }
  if ($element['#default_value'] !== $element['#value']) {
    $currency = _uc_multi_currency_currency_load($element['#value']);
    if ($currency) {
      form_error($element, t('The currency code is already in use.'));
    }
  }
}

/**
 * Validation handler for uc_multi_currency_currency_edit_form().
 */
function uc_multi_currency_currency_edit_form_validate($form, &$form_state) {
  $positive = _uc_multi_currency_process_pattern($form_state['values']['positive']);
  $negative = _uc_multi_currency_process_pattern($form_state['values']['negative']);

  if (!$positive['result']) {
    form_set_error('positive', t('The pattern cannot be interpreted.'));
  }
  if (!$negative['result']) {
    form_set_error('negative', t('The pattern cannot be interpreted.'));
  }

  if ($positive['symbol']) {
    form_set_value($form['symbol'], $positive['symbol'], $form_state);
  }
  else {
    form_set_error('positive', t('The currency symbol is invalid.'));
  }

  if ($positive['grouping'] && strlen($positive['grouping']) < 2 && $negative['grouping'] && $positive['grouping'] == $negative['grouping']) {
    form_set_value($form['group_char'], $positive['grouping'], $form_state);
  }
  else {
    form_set_error('positive', t("The digit grouping character is invalid or doesn't match."));
  }

  if ($positive['decimal'] && strlen($positive['decimal']) == 1 && $negative['decimal'] && $positive['decimal'] == $negative['decimal']) {
    form_set_value($form['dec_char'], $positive['decimal'], $form_state);
  }
  else {
    form_set_error('positive', t("The decimal separator character is invalid or doesn't match."));
  }

  if ($positive['precision'] >= 0 && $positive['precision'] < 5 && $positive['precision'] == $negative['precision']) {
    form_set_value($form['prec'], $positive['precision'], $form_state);
  }
  else {
    form_set_error('positive', t("The number of decimal digits is invalid or doesn't match."));
  }

  form_set_value($form['prefix'], $positive['prefix'], $form_state);
}

/**
 * Returns processed information about a currency display pattern.
 *
 * @param string $pattern
 *   The currency pattern to process.
 *
 * @return array
 *  Associative array with processed details.
 */
function _uc_multi_currency_process_pattern($pattern) {
  $matches = array();
  $result = preg_match('|^([^#]*)#([^#]?)###([^#])(#*)([^#]*)$|i', $pattern, $matches);
  return array(
    'result' => $result,
    'symbol' => empty($matches[1]) ? (empty($matches[5]) ? '' : $matches[5]) : $matches[1],
    'grouping' => empty($matches[2]) ? '' : $matches[2],
    'decimal' => empty($matches[3]) ? '' : $matches[3],
    'precision' => empty($matches[4]) ? 0 : strlen($matches[4]),
    'prefix' => empty($matches[1]) ? FALSE : TRUE,
  );
}

/**
 * Form constructor for the currency delete form.
 *
 * Path: admin/store/settings/currency/%/delete
 *
 * @param string $cid
 *   (Optional) The currency to delete.
 *
 * @see uc_multi_currency_menu()
 * @see uc_multi_currency_currency_delete_form_submit()
 *
 * @ingroup forms
 */
function uc_multi_currency_currency_delete_form($form, &$form_state, $cid) {
  $form['cid_value'] = array(
    '#type' => 'hidden',
    '#value' => $cid,
  );

  $currency = _uc_multi_currency_currency_load($cid);
  return confirm_form($form,
    t('Are you sure you want to delete the currency "!name"? All prices of all products set for this currency will be lost.', array('!name' => $currency->name)),
    'admin/store/settings/currency',
    NULL,
    t('Delete')
    );
}

/**
 * Form submission handler for uc_multi_currency_currency_delete_form().
 */
function uc_multi_currency_currency_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    _uc_multi_currency_currency_delete($form_state['values']['cid_value']);
    drupal_set_message(t('The currency has been deleted.'));
  }
  $form_state['redirect'] = 'admin/store/settings/currency';
}

/**
 * Page callback to toggle the enabled status of a currency.
 *
 * Path: admin/store/settings/currency/%/enable
 *
 * @param string $cid
 *   The currency to toggle.
 */
function uc_multi_currency_currency_enable($cid) {
  $currency = _uc_multi_currency_currency_load($cid);
  if ($currency) {
    $currency->enabled = $currency->enabled ? 0 : 1;
    _uc_multi_currency_currency_save($currency);
    if ($currency->enabled) {
      drupal_set_message(t('The currency %name has been enabled.', array('%name' => $currency->name)));
    }
    else {
      drupal_set_message(t('The currency %name has been disabled.', array('%name' => $currency->name)));
    }
  }
  cache_clear_all('_uc_multi_currency_currency_load', 'cache');
  drupal_goto('admin/store/settings/currency');
}
