/*
 * 从startlink.sx网站提取卫星信息，打开网站后按F12打开开发工具，在控制台执行以下代码
 * 2024-12-03
 */
var g_count = 0;
var g_file_content = '';

function saveToFile(filename, content) {
    const blob = new Blob([content], { type: 'text/plain' }); // 创建一个包含文本的 Blob 对象
    const url = URL.createObjectURL(blob); // 创建一个可供下载的 URL

    const link = document.createElement('a'); // 创建一个下载链接
    link.href = url; // 设置下载链接的地址
    link.download = filename; // 设置下载文件的名称
    link.click(); // 模拟点击，开始下载

    // 清理 URL 对象
    URL.revokeObjectURL(url);
}

function extractOneSatelleteInfo(sate) {
    var values = sate['values_'];

    g_file_content += values['name'] + '; ';
    g_file_content += 'GATEWAY: ' + values['gatewayuuid'] + '; ';
    g_file_content += 'ALTITUDE: ' + Math.round(values['altitude']) + ' KM' + '; ';
    g_file_content += 'STATUS: ' + values['status'] + '; ';
    g_file_content += 'INCLINATION: ' + values['inclination'] + '; ';
    g_file_content += 'LAUNCH: ' + values['launchid'] + '; ';
    g_file_content += 'NORAD ID: ' + values['satid'] + '; ';
    g_file_content += 'CAPACITY: ' + (values['capacity'] / 1000).toFixed(1) + ' GBPS' + '\n';

    if (g_count < 20) {
        console.warn('[' + g_count + ']: ------------------------------------------');
        console.warn(values['name']);
        console.warn('GATEWAY: ' + values['gatewayuuid']);
        console.warn('ALTITUDE: ' + Math.round(values['altitude']) + ' KM');
        console.warn('STATUS: ' + values['status']);
        console.warn('INCLINATION: ' + values['inclination']);
        console.warn('LAUNCH: ' + values['launchid']);
        console.warn('NORAD ID: ' + values['satid']);
        console.warn('CAPACITY: ' + (values['capacity'] / 1000).toFixed(1) + ' GBPS');
    }
    g_count++;
}

function findAllSatellites() {
    // 打印windos所有全局变量
    // for (let key in window) {
    //     if (window.hasOwnProperty(key)) {
    //         console.log(key, window[key]);  // 打印变量名和变量值
    //     }
    // }
    // return;

    var satellites = window['satellites'];
    for (let key in satellites) {
        if (satellites.hasOwnProperty(key)) {
            var sate = satellites[key];
            extractOneSatelleteInfo(sate);
        }
    }
    console.warn('total count: ' + g_count);

    saveToFile('starlink-satelliets.txt', g_file_content);
}

function my_main() {
    findAllSatellites();
}

my_main();