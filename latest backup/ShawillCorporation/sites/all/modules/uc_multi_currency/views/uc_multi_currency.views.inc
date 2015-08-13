<?php

/**
 * Implements hook_views_data().
 */
function uc_multi_currency_views_data() {
  $data = array();
  $path = drupal_get_path('module', 'uc_multi_currency') .'/views';

  $data['uc_orders']['currency_code'] = array(
    'title' => t('Currency code'),
    'help' => t('The currency code of the order.'),
    'real field' => 'data',
    'field' => array(
      'help' => t('The currency code of the order.'),
      'handler' => 'uc_multi_currency_handler_field_currency_code',
      'path' => $path,
    ),
  );
  $data['uc_orders']['currency_name'] = array(
    'title' => t('Currency name'),
    'help' => t('The currency name of the order.'),
    'real field' => 'data',
    'field' => array(
      'help' => t('The currency name of the order.'),
      'handler' => 'uc_multi_currency_handler_field_currency_name',
      'path' => $path,
    ),
  );
 
  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function uc_multi_currency_views_data_alter(&$data) {
  $path = drupal_get_path('module', 'uc_multi_currency') .'/views';

  $data['uc_orders']['order_total']['field']['handler'] = 'uc_multi_currency_handler_field_order_total';
  $data['uc_orders']['order_total']['field']['path'] = $path;
  $data['uc_orders']['order_total_cost']['field']['handler'] = 'uc_multi_currency_handler_field_order_total_cost';
  $data['uc_orders']['order_total_cost']['field']['path'] = $path;

  $data['uc_products']['list_price']['field']['handler'] = 'uc_multi_currency_handler_field_price';
  $data['uc_products']['list_price']['field']['path'] = $path;
  $data['uc_products']['cost']['field']['handler'] = 'uc_multi_currency_handler_field_price';
  $data['uc_products']['cost']['field']['path'] = $path;
  $data['uc_products']['sell_price']['field']['handler'] = 'uc_multi_currency_handler_field_price';
  $data['uc_products']['sell_price']['field']['path'] = $path;
  $data['uc_products']['display_price']['field']['handler'] = 'uc_multi_currency_handler_field_display_price';
  $data['uc_products']['display_price']['field']['path'] = $path;

  $data['uc_products']['is_product']['filter']['handler'] = 'uc_multi_currency_handler_filter_product';
  $data['uc_products']['is_product']['filter']['path'] = $path;
}
