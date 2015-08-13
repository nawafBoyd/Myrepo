<?php

/**
 * Implements hook_token_info().
 */
function uc_multi_currency_token_info() {
  $types = array(
    'uc_multi_currency' => array(
      'name' => t('Currency'),
      'description' => t('Tokens related to Ubercart currencies.'),
      'needs-data' => 'uc_coupon',
    ),
  );

  $tokens = array(
    'uc_order' => array(
      'currency' => array(
        'name' => t('Currency code'),
        'description' => t('The ISO 4217 code of the order currency.'),
      ),
    ),

    'uc_multi_currency' => array(
      'currency-name' => array(
        'name' => t('Currency name'),
        'description' => t('The order currency.'),
      ),
    ),
  );

  return array(
    'types' => $types,
    'tokens' => $tokens,
  );
}

/**
 * Implements hook_tokens().
 */
function uc_multi_currency_tokens($type, $tokens, $data = array(), $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);

  if ($type == 'uc_order' && !empty($data['uc_order'])) {
    $order = $data['uc_order'];
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'currency':
          if (isset($order->data['currency'])) {
            $replacements[$original] = $sanitize ? check_plain($order->currency) : $order->currency;
          }
          break;
        case 'currency-name':
          if (isset($order->data['currency_name'])) {
            $currency = _uc_multi_currency_currency_load($order->currency);
            $replacements[$original] = $sanitize ? check_plain($currency->name) : $currency->name;
          }
          break;
      }
    }
  }

  return $replacements;
}

/**
* Implements hook_tokens_alter().
function uc_multi_currency_tokens_alter(&$replacements,  $context){
  if ($context['type'] == 'uc_order' && !empty($context['data']['uc_order'])) {
    $order = $context['data']['uc_order'];
    if(isset($replacements['subtotal'])){
      $subtotal = '';
      if (is_array($order->line_items)) {
        foreach ($order->line_items as $key => $value) {
          if ($value['type'] == 'subtotal') {
            $subtotal = uc_currency_format($order->line_items[$key]['amount'], $order->currency_symbol);
          }
        }
      }
      $replacements['subtotal'] = $subtotal;
    }
    if(isset($replacements['total'])){
      $replacements['total'] = uc_currency_format($order->order_total, $order->currency_symbol);
    }
  }
}
*/
