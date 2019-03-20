window.onload = function(){
  var scene = new THREE.Scene();

  var camera = new THREE.PerspectiveCamera(75,window.innerWidth/window.innerHeight,0.1,1000);

  camera.position.z = 3;
  camera.position.y = 5;

  var renderer = new THREE.WebGLRenderer();
  renderer.setSize(window.innerWidth, window.innerHeight);
  document.body.appendChild(renderer.domElement);

  var ball_geometry = new THREE.SphereGeometry(4,32,32);
  var ball_material = new THREE.MeshBasicMaterial(
    {map: THREE.ImageUtils.loadTexture('pokeball.png')}
  );
  var ball = new THREE.Mesh(ball_geometry, ball_material);
  ball.matrixAutoUpdate = false;
  scene.add(ball);

  var pole_geometry = new THREE.CylinderGeometry(0.6,0.6,18,32);
  var pole_material = new THREE.MeshBasicMaterial(
    {map: THREE.ImageUtils.loadTexture('pole.png')}
  );
  var pole = new THREE.Mesh(pole_geometry, pole_material);
  pole.matrixAutoUpdate = false;
  scene.add(pole);

  var ground_geometry = new THREE.PlaneGeometry(150,50);
  var ground_material = new THREE.MeshBasicMaterial(
    {map: THREE.ImageUtils.loadTexture('ground.jpg')}
  );
  var ground = new THREE.Mesh(ground_geometry, ground_material);
  ground.matrixAutoUpdate = false;
  scene.add(ground);

  var directionalLight = new THREE.PointLight(0xffffff, 7, 0, 1);
  ball.add(directionalLight);
  pole.add(directionalLight);
  ground.add(directionalLight);

  renderer.setClearColor (0x1e90ff, 1);


  var render = function(){
    var now = new Date();
    var dt = now-(render.time||now);
    render.time = now;

    var ball_tras = new THREE.Matrix4().makeTranslation(0,8,-20);
    var ball_rot = new THREE.Matrix4().makeRotationY( 0.002 * render.time );
    ball.matrix = ball_tras.multiply(ball_rot);

    var pole_tras = new THREE.Matrix4().makeTranslation(0,0,-19);
    var pole_rot = new THREE.Matrix4().makeRotationY(0.002);
    pole.matrix = pole_tras.multiply(pole_rot);

    var ground_tras = new THREE.Matrix4().makeTranslation(0,-7,-20);
    var ground_rot = new THREE.Matrix4().makeRotationX(-Math.PI/2);
    ground.matrix = ground_tras.multiply(ground_rot);

    renderer.render( scene, camera );

    requestAnimationFrame( render );
  }

  render();

}
